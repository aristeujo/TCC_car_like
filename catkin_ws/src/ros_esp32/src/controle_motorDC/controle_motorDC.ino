#define ROSSERIAL_ARDUINO_TCP
#include "kalmanFilter.h"
#include "stateSpaceMatrices.h"
#include "controller.h"
#include "kalmanFilter.h"
#include "motor.h"
#include "AS5600.h"
#include "encoder.h"
#include "WiFi.h"
#include <ros.h>
#include <geometry_msgs/Twist.h>
#include <my_project_msgs/Sensors.h>

void ISR_contador();
void setupWiFi();
void cmdVel_to_pwm_cb( const geometry_msgs::Twist &velocity_msg);

#define FORWARD 1
#define BACKWARD 0
#define STOP 2

#define ENC_IN_A 12 // Fio verde
#define ENC_IN_B 13 // Fio Amarelo
#define potPin  34

IPAddress server(192, 168, 0, 30);
uint16_t serverPort = 11411;
const char*  ssid = "Seixas_Net";
const char*  password = "Mayum647";

ros::NodeHandle  nh;
my_project_msgs::Sensors msg;
ros::Publisher chatter("/sensors_values", &msg);
ros::Subscriber<geometry_msgs::Twist> sub("/cmd_vel", &cmdVel_to_pwm_cb );

Motor motor(19,18,4,22);
Encoder encoder;

AS5600 as5600_0(&Wire);
AS5600 as5600_1(&Wire1);

KalmanFilter motorFilter(sysX.A, sysX.B, sysX.C, 3.5e-2, 1e-3);
Controller Controller({-4.8697, -2.4895}, {2.49});
//Controller Controller({-4.8697, -2.4895}, {0});

Matrix<2, 1> states = {0, 0};
Matrix<1> y;
float u = 0;

unsigned long timer = 0;
unsigned long intervalo = 100;

void setup() {

  Serial.begin(115200);
  pinMode(2, OUTPUT);
  setupWiFi();
  nh.getHardware()->setConnection(server, serverPort);
  nh.initNode();
  nh.advertise(chatter);
  nh.subscribe(sub);
  
  Wire.begin();
  motor.initMotor();

  pinMode(potPin, INPUT);  
  pinMode(ENC_IN_A , INPUT_PULLUP);
  pinMode(ENC_IN_B , INPUT);
  
  attachInterrupt(digitalPinToInterrupt(ENC_IN_A), ISR_contador, RISING);

  encoder.setEncoder_AS5600(as5600_0, 23); 
  
  motor.motorSpeed(0, STOP);
  motor.setAngle(motor.angulo_frente);
  Serial.println("End of Setup");

  delay(1000);
}

void loop() {
  int val = map(analogRead(potPin), 0, 4095, 0, 255);
  //  Controller.r(0) = val;

  if (millis() - timer >= intervalo) {
    float enc_as5600 = encoder.getRPM_AS5600(as5600_0);
    float rpm = encoder.getRPM_MotorEixo(intervalo);
    // y(0) = rpm;
    
    // states = motorFilter.kalman(u, rpm);
    // u = Controller.controlLaw(states, y); 
    // saturate(&u,0,255);  
    motor.motorSpeed(val, FORWARD);
    // Serial.printf("RPM:%.2f\n", encoder.rpm);
    Serial.printf("RPM:%.2f  AS5600: %.2f\n", rpm, enc_as5600);
    // Serial.printf("r:%.2f  x_hat:%.2f y: %.2f\n", Controller.r(0), states(0), rpm);
    
    msg.encoder_eixo = rpm;
    msg.encoder_as5600_L = enc_as5600;
    msg.encoder_as5600_R = 110;   
    chatter.publish(&msg);
    nh.spinOnce();

    timer = millis();
  }

}

void ISR_contador(){
  int val = digitalRead(ENC_IN_B);

  if (val == LOW) {
    encoder.direcao = true; // Trás
  }
  else {
    encoder.direcao = false; // Frente
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

void cmdVel_to_pwm_cb( const geometry_msgs::Twist &velocity_msg){

    float right_wheel = (velocity_msg.linear.x + velocity_msg.angular.z ) / 2 ;
    float left_wheel = (velocity_msg.linear.x - velocity_msg.angular.z ) /2 ;

    Serial.print(left_wheel);Serial.print(" / ");Serial.println(right_wheel);

}