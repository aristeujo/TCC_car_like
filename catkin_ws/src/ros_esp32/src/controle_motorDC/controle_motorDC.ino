#define ROSSERIAL_ARDUINO_TCP
#include "WiFi.h"
#include "kalmanFilter.h"
#include "stateSpaceMatrices.h"
#include "controller.h"
#include "kalmanFilter.h"
#include "motor.h"
#include "encoder.h"
#include "AS5600.h"
#include "giroscopio.h"
#include <ros.h>
#include <my_project_msgs/Sensors.h>
#include <my_project_msgs/Command_ackermann.h>

void ISR_contador();
void setupWiFi();
void cmdVel_to_pwm( const my_project_msgs::Command_ackermann &cmd);

#define FORWARD 0
#define BACKWARD 1
#define STOP 2

#define ENC_IN_A 12 // Fio verde
#define ENC_IN_B 13 // Fio Amarelo
#define potPin  34

// IPAddress server(192, 168, 0, 30); //IP do/ desktop da minha casa

// IPAddress server(192, 168, 15, 6); //IP do/ desktop do Graest

//IPAddress server(192,169,141,72); //IP do /notebook do STEM

IPAddress server(192,168,8,253); //IP do /notebook do STEM


uint16_t serverPort = 11411;
//const char*  ssid = "Seixas_Net";
//const char*  password = "Mayum647";

//const char*  ssid = "STEMLABNET";
//const char*  password = "1n0v@t3ch.5t3m@#!";

//const char*  ssid = "NucleoRobotica2g";
//const char*  password = "!gra.3st#";

const char*  ssid = "Teste";
const char*  password = "12345678";


ros::NodeHandle  nh;
my_project_msgs::Sensors msg;
ros::Publisher chatter("/sensors_values", &msg);
ros::Subscriber<my_project_msgs::Command_ackermann> sub("/cmd_car", &cmdVel_to_pwm);

Motor motor(18,19,4,27);
Encoder encoder;

int r = 0;
int pwm = 0;
float u = 0;
float angle = 92;
float error = 0;
int state = 0;

//bateria antiga
//float Kp = 1.9178;
//float Ki = 0.5434;

// bateria nova
float Kp = 0.9672;
float Ki = 0.5682;

TwoWire Wire_1 = TwoWire(1);

AS5600 as5600_0(&Wire);
AS5600 as5600_1(&Wire_1);

Giroscopio mpu6050;

unsigned long timer = 0;
unsigned long intervalo = 100;

void setup() {
  Serial.begin(115200);
  pinMode(2, OUTPUT);
  setupWiFi();

//  delay(2000);
  
  nh.getHardware()->setConnection(server, serverPort);
  nh.initNode();
  nh.advertise(chatter);
  nh.subscribe(sub);
  
  motor.initMotor();

  pinMode(potPin, INPUT);  
  pinMode(ENC_IN_A , INPUT_PULLUP);
  pinMode(ENC_IN_B , INPUT);
  
  attachInterrupt(digitalPinToInterrupt(ENC_IN_A), ISR_contador, RISING);
  Wire.begin(21,22);
  as5600_0.begin(5);
  as5600_0.setDirection(AS5600_CLOCK_WISE);
  int a = as5600_0.isConnected();
  Serial.print("Connect: ");
  Serial.println(a);
  encoder.setEncoder_AS5600(as5600_1, 32,33,25, Wire_1); 

  mpu6050.setup_giro();
  
  motor.motorSpeed(0, STOP);
  motor.setAngle(motor.angulo_frente);
  Serial.println("End of Setup");

  delay(1000);
}

void loop() {
  // int r = map(analogRead(potPin), 0, 4095, 0, 280);

  // update MPU6050 communication
  mpu6050.update_mpu();

  // Loop every 100 ms
  if (millis() - timer >= intervalo) {
//    long temp = millis();
    mpu6050.get_data();

    // Read sensor data
    float enc_as5600_L = encoder.getRPM_AS5600(as5600_0);
    float enc_as5600_R = encoder.getRPM_AS5600(as5600_1);
    float rpm = encoder.getRPM_MotorEixo(intervalo);
    float angularVelocity = mpu6050.angularVelocityZ; 

    // offset stop state
    if(abs(enc_as5600_L) < 2.0){
      enc_as5600_L = 0.0;
    }
    else if(abs(enc_as5600_R) < 2.0){
      enc_as5600_R = 0.0;
    }

     // Update control signal
//     error += r - rpm; 
//     u = Kp*(r - rpm) + Ki*error;
//     saturate(&u,0,230);  

     // Publish in ROS topic
     msg.encoder_eixo = rpm;
     msg.encoder_as5600_L = enc_as5600_L;
     msg.encoder_as5600_R = enc_as5600_R; 
     msg.angularVelocity = angularVelocity;
     chatter.publish(&msg);

      // Debug info
//      Serial.printf("r:%d RPM:%.2f u:%.2f\n",r, rpm, angle);
//    Serial.printf("RPM:%.2f  AS5600_L: %.2f  AS5600_R: %.2f  Z_angle: %.2f\n", rpm, enc_as5600_L, enc_as5600_R, mpu6050.angularVelocityZ);
//     Serial.printf("r:%.2f  x_hat:%.2f y: %.2f\n", Controller.r(0), states(0), rpm);
     motor.motorSpeed(r, state); // Min = 150 || Max = 230
     motor.setAngle(angle);
     
     timer = millis();
//     Serial.println(timer - temp);
  }

  nh.spinOnce();
  
//  motor.motorSpeed(u, FORWARD); // Min = 150 || Max = 230
//  motor.setAngle(130);
}

 void ISR_contador(){
   int val = digitalRead(ENC_IN_B);

   if (val == LOW) {
     encoder.direcao = false; // Trás
   }
   else {
     encoder.direcao = true; // Frente
   }

   if (encoder.direcao) {
     encoder.pulsos_roda++;
   }
   else {
     encoder.pulsos_roda--;
   }
 };

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
     r = abs(motor_speed); 

     angle = steering_angle;

//     Serial.println(angle);
 }
