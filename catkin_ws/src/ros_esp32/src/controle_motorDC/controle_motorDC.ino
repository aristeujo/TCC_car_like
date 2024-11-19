#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/semphr.h>
#include "WiFi.h"
#include "motor.h"
#include "encoder_as5600.h"
#include "AS5600.h"
#include "MPU6050Handler.h"
#include <ros.h>
#include <my_project_msgs/Sensors.h>
#include <my_project_msgs/Command_ackermann.h>

void setupWiFi();
void cmdVel_to_pwm( const my_project_msgs::Command_ackermann &cmd);

SemaphoreHandle_t i2cMutex;
QueueHandle_t sensorDataQueue;

#define FORWARD 0
#define BACKWARD 1
#define STOP 2

const int ENC_COUNT_REV = 375;
unsigned long intervalo = 100;

#define ENC_A 12 // Canal A do encoder
#define ENC_B 13 // Canal B do encoder
#define potPin 34

//IPAddress server(192, 168, 0, 32);/
IPAddress server(192, 168, 15, 39);
uint16_t serverPort = 11411;

const char* ssid = "NucleoRobotica2g";
const char* password = "!gra.3st#";

ros::NodeHandle nh;
my_project_msgs::Sensors msg;
ros::Publisher chatter("/sensors_values", &msg);
my_project_msgs::Command_ackermann cmd;
ros::Subscriber<my_project_msgs::Command_ackermann> sub("/cmd_car", &cmdVel_to_pwm);

Motor motor(18, 19, 4, 27);
TwoWire Wire_1 = TwoWire(1);
AS5600 as5600_0(&Wire);
AS5600 as5600_1(&Wire_1);

Encoder encoder0(i2cMutex);
Encoder encoder1(i2cMutex);

MPU6050Handler mpu6050Handler(Wire, i2cMutex);

volatile int32_t pulses_motor = 0;
int r = 0;
float angle = 92;
int state = STOP;
int delay_control = 98;

TaskHandle_t taskHandleSensorRead;
TaskHandle_t taskHandlePublishROS;
TaskHandle_t taskHandleMotorControl;
TaskHandle_t taskHandleScheduler;

struct SensorData {
    float rpm;
    float enc_as5600_L;
    float enc_as5600_R;
    float accX, accY, accZ;
    float gyroX, gyroY, gyroZ;
    float temperature;
};

void check_channel_A();
void check_channel_B();

void TaskSensorRead(void *pvParameters);
void TaskPublishROS(void *pvParameters);
void TaskMotorControl(void *pvParameters);
void TaskScheduler(void *pvParameters);

void setup() {
    Serial.begin(115200);
    Wire.begin(21, 22);
    pinMode(2, OUTPUT);
    setupWiFi();

    nh.getHardware()->setConnection(server, serverPort);
    nh.initNode();
    nh.advertise(chatter);
    nh.subscribe(sub);

    i2cMutex = xSemaphoreCreateMutex();
    sensorDataQueue = xQueueCreate(10, sizeof(SensorData));

    if (!i2cMutex || !sensorDataQueue) {
        Serial.println("Failed to create FreeRTOS resources!");
        while (1);
    }

    if (!mpu6050Handler.initialize()) {
        while (1);
    }

    encoder0.setEncoder_AS5600(as5600_0, 21, 22, 5, Wire);
    encoder1.setEncoder_AS5600(as5600_1, 32, 33, 25, Wire_1);

    motor.initMotor();
    pinMode(potPin, INPUT);

    // Configuração dos pinos de interrupção
    pinMode(ENC_A, INPUT_PULLUP);
    pinMode(ENC_B, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(ENC_A), check_channel_A, CHANGE);
    attachInterrupt(digitalPinToInterrupt(ENC_B), check_channel_B, CHANGE);

    xTaskCreate(TaskSensorRead, "TaskSensorRead", 2048, NULL, 4, &taskHandleSensorRead);
    xTaskCreate(TaskPublishROS, "TaskPublishROS", 2048, NULL, 2, &taskHandlePublishROS);
    xTaskCreate(TaskMotorControl, "TaskMotorControl", 2048, NULL, 3, &taskHandleMotorControl);
    xTaskCreate(TaskScheduler, "TaskScheduler", 2048, NULL, 4, &taskHandleScheduler);

    motor.motorSpeed(0, STOP);
    motor.setAngle(motor.angulo_frente);
    Serial.println("End of Setup");
}

void loop() {
    nh.spinOnce();
    vTaskDelay(1);
}

void TaskSensorRead(void *pvParameters) {
    while (1) {
        SensorData data;

        // Atualiza e coleta dados do MPU6050
        mpu6050Handler.update();
        MPUData mpuData = mpu6050Handler.getData();

        data.rpm = (pulses_motor*(60.0*1000.0)/(intervalo*ENC_COUNT_REV));
        data.enc_as5600_L = encoder0.getRPM_AS5600(as5600_0);
        data.enc_as5600_R = encoder1.getRPM_AS5600(as5600_1);
        data.accX = mpuData.accX;
        data.accY = mpuData.accY;
        data.accZ = mpuData.accZ;
        data.gyroX = mpuData.gyroX;
        data.gyroY = mpuData.gyroY;
        data.gyroZ = mpuData.gyroZ;
        data.temperature = mpuData.temperature;

        if (xQueueSend(sensorDataQueue, &data, pdMS_TO_TICKS(50)) != pdPASS) {
            Serial.println("Failed to send to queue");
        }

        vTaskDelay(pdMS_TO_TICKS(50));
    }
}

void TaskPublishROS(void *pvParameters) {
    while (1) {
        SensorData data;
        if (xQueueReceive(sensorDataQueue, &data, pdMS_TO_TICKS(100)) == pdPASS) {
            msg.encoder_eixo = data.rpm;
            msg.angularVelocity = data.gyroZ;
            msg.encoder_as5600_L = data.enc_as5600_L;
            msg.encoder_as5600_R = data.enc_as5600_R;

            chatter.publish(&msg);

        Serial.printf("RPM:%.2f  AS5600_L: %.2f  AS5600_R: %.2f omega_Z: %.2f\n", data.rpm, data.enc_as5600_L, data.enc_as5600_R, data.gyroZ);

        } else {
            Serial.println("No data available in queue");
        }

        vTaskDelay(pdMS_TO_TICKS(delay_control));
    }
}

void TaskMotorControl(void *pvParameters) {
    while (1) {
        motor.motorSpeed(r, state);
        motor.setAngle(angle);
        vTaskDelay(pdMS_TO_TICKS(delay_control));
    }
}

void TaskScheduler(void *pvParameters) {
    while (1) {
        if (state == FORWARD || state == BACKWARD) {
            vTaskPrioritySet(taskHandleMotorControl, 4);
            vTaskPrioritySet(taskHandleSensorRead, 3);
            vTaskPrioritySet(taskHandlePublishROS, 1);
        } else {
            vTaskPrioritySet(taskHandleMotorControl, 3);
            vTaskPrioritySet(taskHandleSensorRead, 2);
            vTaskPrioritySet(taskHandlePublishROS, 2);
        }
        vTaskDelay(pdMS_TO_TICKS(delay_control));
    }
}

void setupWiFi(){  
   WiFi.begin(ssid, password);
   while (WiFi.status() != WL_CONNECTED) { delay(500);Serial.print("."); }
   Serial.print("SSID: ");
   Serial.println(WiFi.SSID());
   Serial.print("IP:   ");
   Serial.println(WiFi.localIP());
   digitalWrite(2, HIGH);

}

 void cmdVel_to_pwm(const my_project_msgs::Command_ackermann &cmd){

     float motor_speed = cmd.rpm;
     float steering_angle = cmd.servo_angle;

     if(motor_speed > 5){
      state = FORWARD;
     }

     else if(motor_speed < -5){
      state = BACKWARD;
     }

     else if(motor_speed == 0){
      state = STOP;
     }

     // RPM setpoint
     r = floor(abs(motor_speed)); 

     angle = steering_angle;

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
