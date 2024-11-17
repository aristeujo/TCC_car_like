#define ROSSERIAL_ARDUINO_TCP
#include "WiFi.h"
#include "motor.h"
#include "encoder.h"
#include "AS5600.h"
#include "giroscopio.h"
#include <ros.h>
#include <my_project_msgs/Sensors.h>
#include <my_project_msgs/Command_ackermann.h>

SemaphoreHandle_t i2cMutex;

void ISR_contador();
void setupWiFi();
void cmdVel_to_pwm(const my_project_msgs::Command_ackermann &cmd);

#define FORWARD 0
#define BACKWARD 1
#define STOP 2

#define ENC_IN_A 12
#define ENC_IN_B 13
#define potPin  34

IPAddress server(192, 168, 0, 32);
uint16_t serverPort = 11411;

const char* ssid = "Seixas_Net";
const char* password = "Mayum647";

ros::NodeHandle nh;
my_project_msgs::Sensors msg;
ros::Publisher chatter("/sensors_values", &msg);
ros::Subscriber<my_project_msgs::Command_ackermann> sub("/cmd_car", &cmdVel_to_pwm);

TwoWire Wire_1 = TwoWire(1);
Motor motor(18, 19, 4, 27);
AS5600 as5600_0(&Wire);
AS5600 as5600_1(&Wire_1);
Giroscopio mpu6050(Wire, i2cMutex);
Encoder encoder(i2cMutex);

int r = 0;
float angle = 92;
int state = STOP;

void TaskSensorRead(void *pvParameters);
void TaskPublishROS(void *pvParameters);
void TaskMotorControl(void *pvParameters);

void setup() {
  Serial.begin(115200);
  pinMode(2, OUTPUT);
  setupWiFi();

  nh.getHardware()->setConnection(server, serverPort);
  nh.initNode();
  nh.advertise(chatter);
  nh.subscribe(sub);

  i2cMutex = xSemaphoreCreateMutex();

  motor.initMotor();
  pinMode(potPin, INPUT);
  pinMode(ENC_IN_A, INPUT_PULLUP);
  pinMode(ENC_IN_B, INPUT);
  attachInterrupt(digitalPinToInterrupt(ENC_IN_A), ISR_contador, RISING);

  mpu6050.setup_giro();
  encoder.setEncoder_AS5600(as5600_0, 21, 22, 23, Wire);
  encoder.setEncoder_AS5600(as5600_1, 32, 33, 25, Wire_1);

  xTaskCreate(TaskSensorRead, "TaskSensorRead", 2048, NULL, 2, NULL);
  xTaskCreate(TaskPublishROS, "TaskPublishROS", 2048, NULL, 1, NULL);
  xTaskCreate(TaskMotorControl, "TaskMotorControl", 2048, NULL, 3, NULL);

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
    mpu6050.update_mpu();
    mpu6050.get_data();
    encoder.getRPM_AS5600(as5600_0);
    encoder.getRPM_AS5600(as5600_1);
    encoder.getRPM_MotorEixo(100);
    vTaskDelay(pdMS_TO_TICKS(50));
  }
}

void TaskPublishROS(void *pvParameters) {
  while (1) {
    float rpm = encoder.getRPM_MotorEixo(100);
    float angularVelocity = mpu6050.angularVelocityZ;
    float enc_as5600_L = encoder.getRPM_AS5600(as5600_0);
    float enc_as5600_R = encoder.getRPM_AS5600(as5600_1);

    msg.encoder_eixo = rpm;
    msg.encoder_as5600_L = enc_as5600_L;
    msg.encoder_as5600_R = enc_as5600_R;
    msg.angularVelocity = angularVelocity;
    chatter.publish(&msg);

    vTaskDelay(pdMS_TO_TICKS(100));
  }
}

void TaskMotorControl(void *pvParameters) {
  while (1) {
    motor.motorSpeed(r, state);
    motor.setAngle(angle);
    vTaskDelay(pdMS_TO_TICKS(10));
  }
}

void ISR_contador() {
  int val = digitalRead(ENC_IN_B);
  encoder.direcao = (val == LOW) ? true : false;
  encoder.pulsos_roda += (encoder.direcao) ? 1 : -1;
}

void setupWiFi() {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi conectado");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
  digitalWrite(2, HIGH);
}

void cmdVel_to_pwm(const my_project_msgs::Command_ackermann &cmd) {
  float motor_speed = cmd.rpm;
  float steering_angle = cmd.servo_angle;

  if (motor_speed > 5) {
    state = FORWARD;
  } else if (motor_speed < -5) {
    state = BACKWARD;
  } else {
    state = STOP;
  }

  r = floor(abs(motor_speed));
  angle = steering_angle;
}
