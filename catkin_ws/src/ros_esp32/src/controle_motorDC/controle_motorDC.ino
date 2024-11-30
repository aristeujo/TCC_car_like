#include <Arduino.h>
//#include <freertos/FreeRTOS.h>
//#include <freertos/task.h>
//#include <freertos/semphr.h>
#include "WiFi.h"
#include "MPU6050Handler.h"
#include "motor.h"
#include "encoder_as5600.h"
#include "AS5600.h"
#include <ros.h>
#include <my_project_msgs/Sensors.h>
#include <my_project_msgs/TasksGantt.h>
#include <my_project_msgs/TaskState.h>
#include <my_project_msgs/Command_ackermann.h>

// WiFi Configuração
void setupWiFi();
void cmdVel_to_pwm(const my_project_msgs::Command_ackermann &cmd);

// Mutex e fila
SemaphoreHandle_t i2cMutex;
SemaphoreHandle_t logMutex;
QueueHandle_t sensorDataQueue;

// Definições de controle
#define FORWARD 0
#define BACKWARD 1
#define STOP 2

// Encoder
const int ENC_COUNT_REV = 1380;

// GPIO Pins
#define ENC_A 12
#define ENC_B 13
#define potPin 34

IPAddress server(192, 168, 15, 39);
uint16_t serverPort = 11411;

// WiFi
const char* ssid = "NucleoRobotica2g";
const char* password = "!gra.3st#";

// ROS
ros::NodeHandle nh;
my_project_msgs::Sensors msg;
ros::Publisher chatter("/sensors_values", &msg);
my_project_msgs::Command_ackermann cmd;
ros::Subscriber<my_project_msgs::Command_ackermann> sub("/cmd_car", &cmdVel_to_pwm);

// Publicador para os dados do Gantt
my_project_msgs::TasksGantt ganttMsg;
ros::Publisher ganttPublisher("/tasks_gantt", &ganttMsg);

// Estruturas de dados
struct TaskLog {
    int taskIndex;
    const char* state;
    unsigned long timestamp;
};

struct SensorData {
    float rpm;
    float enc_as5600_L;
    float enc_as5600_R;
    float accX, accY, accZ;
    float gyroX, gyroY, gyroZ;
    float temperature;
};

// Buffer de logs
#define LOG_BUFFER_SIZE 256
my_project_msgs::TaskState taskStatesBuffer[LOG_BUFFER_SIZE];
TaskLog taskLogs[LOG_BUFFER_SIZE];
int logIndex = 0;

// Handles das tarefas
TaskHandle_t taskHandleSensorRead;
TaskHandle_t taskHandlePublishROS;
TaskHandle_t taskHandleMotorControl;
TaskHandle_t taskHandleSendGantt;

unsigned long wcetTaskSensorRead = 0;
unsigned long wcetTaskPublishROS = 0;
unsigned long wcetTaskMotorControl = 0;
unsigned long wcetTaskSendGantt = 0;

// Motor e sensores
Motor motor(18, 19, 4, 27);
TwoWire Wire_1 = TwoWire(1);
AS5600 as5600_0(&Wire);
AS5600 as5600_1(&Wire_1);
Encoder encoder0(i2cMutex);
Encoder encoder1(i2cMutex);
MPU6050Handler mpu6050Handler(Wire, i2cMutex);

// Variáveis globais
volatile int32_t pulses_motor = 0;
int r = 0;
float angle = 92;
int state = STOP;
int delay_control = 95;

// Funções auxiliares
void logTaskState(int taskIndex, const char* state);
void sendGanttData();

// Prototipação das tarefas
void TaskSensorRead(void *pvParameters);
void TaskPublishROS(void *pvParameters);
void TaskMotorControl(void *pvParameters);
void TaskSendGantt(void *pvParameters);

void setup() {
    Serial.begin(115200);
    Wire.begin(21, 22);
    pinMode(2, OUTPUT);
    setupWiFi();

    // Inicializa ROS
    nh.getHardware()->setConnection(server, serverPort);
    nh.initNode();
    nh.advertise(chatter);
    nh.advertise(ganttPublisher);
    nh.subscribe(sub);

    // Cria Mutexes e fila
    i2cMutex = xSemaphoreCreateMutex();
    logMutex = xSemaphoreCreateMutex();
    sensorDataQueue = xQueueCreate(150, sizeof(SensorData));

    if (!i2cMutex || !logMutex || !sensorDataQueue) {
        Serial.println("Failed to create FreeRTOS resources!");
        while (1);
    }

    if (!mpu6050Handler.initialize()) {
        while (1);
    }

    // Inicializa encoders
    encoder0.setEncoder_AS5600(as5600_0, 21, 22, 5, Wire);
    encoder1.setEncoder_AS5600(as5600_1, 32, 33, 25, Wire_1);

    // Inicializa motor
    motor.initMotor();
    pinMode(potPin, INPUT);

    // Configura interrupções
    pinMode(ENC_A, INPUT_PULLUP);
    pinMode(ENC_B, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(ENC_A), check_channel_A, CHANGE);
    attachInterrupt(digitalPinToInterrupt(ENC_B), check_channel_B, CHANGE);

    // Cria tarefas
    xTaskCreate(TaskSensorRead, "TaskSensorRead", 2048, NULL, 2, &taskHandleSensorRead);
    xTaskCreate(TaskPublishROS, "TaskPublishROS", 2048, NULL, 3, &taskHandlePublishROS);
    xTaskCreate(TaskMotorControl, "TaskMotorControl", 2048, NULL, 4, &taskHandleMotorControl);
    xTaskCreate(TaskSendGantt, "TaskSendGantt", 4096, NULL, 1, &taskHandleSendGantt);

    motor.motorSpeed(0, STOP);
    motor.setAngle(motor.angulo_frente);
    Serial.println("End of Setup");
}

void loop() {
    nh.spinOnce();
    monitorWCET();
//    vTaskDelay(1);
}

void monitorWCET() {
    Serial.printf("WCET TaskSensorRead: %lu us\n", wcetTaskSensorRead);
    Serial.printf("WCET TaskPublishROS: %lu us\n", wcetTaskPublishROS);
    Serial.printf("WCET TaskMotorControl: %lu us\n", wcetTaskMotorControl);
    Serial.printf("WCET TaskSendGantt: %lu us\n", wcetTaskSendGantt);
    Serial.println("========================================");
}


void logTaskState(int taskIndex, const char* state) {
    if (xSemaphoreTake(logMutex, portMAX_DELAY)) {
        if (logIndex < LOG_BUFFER_SIZE) {
            taskLogs[logIndex].taskIndex = taskIndex;
            taskLogs[logIndex].state = state;
            taskLogs[logIndex].timestamp = micros(); // Alterado para usar micros()
            logIndex++;
        } else {
            Serial.println("Log buffer is full!");
        }
        xSemaphoreGive(logMutex);
    }
}

void sendGanttData() {
    if (xSemaphoreTake(logMutex, portMAX_DELAY)) {
        int numLogs = logIndex > LOG_BUFFER_SIZE ? LOG_BUFFER_SIZE : logIndex;

        ganttMsg.task_states_length = numLogs;
        for (int i = 0; i < numLogs; i++) {
            taskStatesBuffer[i].task_index = taskLogs[i].taskIndex;
            taskStatesBuffer[i].state = strcmp(taskLogs[i].state, "active") == 0 ? 0 : 1;
            taskStatesBuffer[i].timestamp = taskLogs[i].timestamp; // Já está em micros()
        }

        // Adiciona os WCETs à mensagem
        ganttMsg.wcet_sensor_read = wcetTaskSensorRead / 1000.0; // Converte para ms
        ganttMsg.wcet_publish_ros = wcetTaskPublishROS / 1000.0; // Converte para ms
        ganttMsg.wcet_motor_control = wcetTaskMotorControl / 1000.0; // Converte para ms
        ganttMsg.wcet_send_gantt = wcetTaskSendGantt / 1000.0; // Converte para ms

        ganttMsg.task_states = taskStatesBuffer;
        ganttPublisher.publish(&ganttMsg);

        logIndex = 0;
        xSemaphoreGive(logMutex);
    }
}



void TaskSensorRead(void *pvParameters) {
    TickType_t lastWakeTime = xTaskGetTickCount();
    while (1) {
        unsigned long startTime = micros(); // Tempo de início
        logTaskState(0, "active");
        SensorData data;

        mpu6050Handler.update();
        MPUData mpuData = mpu6050Handler.getData();

        data.rpm = (pulses_motor * (60.0 * 1000.0) / (20 * ENC_COUNT_REV));
        data.enc_as5600_L = encoder0.getRPM_AS5600(as5600_0);
        data.enc_as5600_R = encoder1.getRPM_AS5600(as5600_1);
        data.gyroZ = mpuData.gyroZ;

        if (xQueueSend(sensorDataQueue, &data, pdMS_TO_TICKS(10)) != pdPASS) {
//            Serial.println("Queue Full");
        }
        pulses_motor = 0;

        logTaskState(0, "idle");
        unsigned long execTime = micros() - startTime; // Tempo de execução
        if (execTime > wcetTaskSensorRead) {
            wcetTaskSensorRead = execTime; // Atualiza WCET se maior
        }
        vTaskDelayUntil(&lastWakeTime, pdMS_TO_TICKS(20));
    }
}

void TaskPublishROS(void *pvParameters) {
    TickType_t lastWakeTime = xTaskGetTickCount();
    while (1) {
        unsigned long startTime = micros();
        logTaskState(1, "active");
        SensorData data;
        if (xQueueReceive(sensorDataQueue, &data, pdMS_TO_TICKS(delay_control)) == pdPASS) {
            msg.encoder_eixo = data.rpm;
            msg.angularVelocity = data.gyroZ;
            msg.encoder_as5600_L = data.enc_as5600_L;
            msg.encoder_as5600_R = data.enc_as5600_R;
            chatter.publish(&msg);

//            Serial.printf("Publishing ROS Message: encoder_eixo=%.2f, angularVelocity=%.2f, encoder_as5600_L=%.2f, encoder_as5600_R=%.2f\n", 
//            msg.encoder_eixo, 
//            msg.angularVelocity, 
//            msg.encoder_as5600_L, 
//            msg.encoder_as5600_R);
        }
        logTaskState(1, "idle");
        unsigned long execTime = micros() - startTime;
        if (execTime > wcetTaskPublishROS) {
            wcetTaskPublishROS = execTime;
        }
        vTaskDelayUntil(&lastWakeTime, pdMS_TO_TICKS(delay_control));
    }
}

void TaskMotorControl(void *pvParameters) {
    TickType_t lastWakeTime = xTaskGetTickCount();
    while (1) {
        unsigned long startTime = micros(); // Tempo de início
        logTaskState(2, "active");

        motor.motorSpeed(r, state);
        motor.setAngle(angle);

        logTaskState(2, "idle");
        unsigned long execTime = micros() - startTime; // Tempo de execução
        if (execTime > wcetTaskMotorControl) {
            wcetTaskMotorControl = execTime; // Atualiza WCET se maior
        }
        vTaskDelayUntil(&lastWakeTime, pdMS_TO_TICKS(delay_control));
    }
}


void TaskSendGantt(void *pvParameters) {
    TickType_t lastWakeTime = xTaskGetTickCount();
    while (1) {
        unsigned long startTime = micros(); // Tempo de início
        logTaskState(3, "active");

        sendGanttData();

        logTaskState(3, "idle");
        unsigned long execTime = micros() - startTime; // Tempo de execução
        if (execTime > wcetTaskSendGantt) {
            wcetTaskSendGantt = execTime; // Atualiza WCET se maior
        }
        vTaskDelayUntil(&lastWakeTime, pdMS_TO_TICKS(100)); // Período de 100 ms
    }
}


void setupWiFi() {
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.print("SSID: ");
    Serial.println(WiFi.SSID());
    Serial.print("IP:   ");
    Serial.println(WiFi.localIP());
}

void cmdVel_to_pwm(const my_project_msgs::Command_ackermann &cmd) {
    float motor_speed = cmd.rpm;
    float steering_angle = cmd.servo_angle;

    if (motor_speed > 5) {
        state = FORWARD;
    } else if (motor_speed < -5) {
        state = BACKWARD;
    } else if (motor_speed == 0) {
        state = STOP;
    }

    r = floor(abs(motor_speed));
    angle = steering_angle;

    Serial.println(r);
}

void check_channel_A() {
    if (digitalRead(ENC_A) == HIGH) {
        if (digitalRead(ENC_B) == LOW) {
            pulses_motor++;
        } else {
            pulses_motor--;
        }
    } else {
        if (digitalRead(ENC_B) == HIGH) {
            pulses_motor++;
        } else {
            pulses_motor--;
        }
    }
}

void check_channel_B() {
    if (digitalRead(ENC_B) == HIGH) {
        if (digitalRead(ENC_A) == HIGH) {
            pulses_motor++;
        } else {
            pulses_motor--;
        }
    } else {
        if (digitalRead(ENC_A) == LOW) {
            pulses_motor++;
        } else {
            pulses_motor--;
        }
    }
}
