#include "kalmanFilter.h"
#include "stateSpaceMatrices.h"
#include "controller.h"
#include "kalmanFilter.h"
#include <ESP32Servo.h>
#include "encoder.h"

void motorSpeed(int velocidade, int sentido);

#define FORWARD 1
#define BACKWARD 0
#define STOP 2

float MIN_DUTYCYCLE = 0;  //0 - 255 (125)
float MAX_DUTYCYCLE = 255; //0 - 255 (255)

KalmanFilter motorFilter(sysX.A, sysX.B, sysX.C, 3e-4, 1e-5);
Controller xController({-4.8697, -2.4895});

Matrix<2, 1> statesX = {0, 0};

float uX = 0;

Servo servo;
const int freq = 5000;
const int pwmChannel = 2;
const int resolution = 8;

int motorPin1 = 19;
int motorPin2 = 18;
int enablePin = 4;
int servoPin = 22;

long previousMillis = 0;
unsigned long timer = 0;
unsigned long intervalo = 100;

int sinal_controle = 0;
int angulo_frente = 98;

Matrix<1> y;

const float dt = 0.1;

void setup() {

  Serial.begin(115200);
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(enablePin, OUTPUT);

  setEncoder();

  servo.setPeriodHertz(50);    // standard 50 hz servo
  servo.attach(servoPin, 1000, 2000); // attaches the servo on pin 15 to the servo object

  ledcSetup(pwmChannel, freq, resolution);
  ledcAttachPin(enablePin, pwmChannel);

//  xController.Ki = {2.49};

  motorSpeed(0, STOP);
  servo.write(angulo_frente);

  xController.r(0) = 130;

  Serial.println("End of Setup");
}

void loop() {

  if (millis() - timer >= intervalo) {

    calculoVelocidade(intervalo);

    y(0) = rpm;
    
    statesX = motorFilter.kalman(uX, rpm);
    
    xController.controlLaw(statesX, y); 
    uX = xController.u(0);
    saturate(&uX,MIN_DUTYCYCLE,MAX_DUTYCYCLE);  
    motorSpeed(uX, FORWARD);

    Serial.printf("X:%f  RPM: %f\n", statesX(0), xController.Ki(1));
    timer = millis();
  }
}

void motorSpeed(int velocidade, int sentido) {

  switch (sentido) {
    case 0: //Forward
      digitalWrite(motorPin1, HIGH);
      digitalWrite(motorPin2, LOW);
      ledcWrite(pwmChannel, velocidade);
      break;

    case 1: //BackWard
      digitalWrite(motorPin1, LOW);
      digitalWrite(motorPin2, HIGH);
      ledcWrite(pwmChannel, velocidade);
      break;

    case 2: // Stop
      digitalWrite(motorPin1, LOW);
      digitalWrite(motorPin2, LOW);
      ledcWrite(pwmChannel, velocidade);
      break;

    default:
      break;
  }
};




// controle
//
//MotorSpeedModel modelMotor(0.9558, -0.2512, 0.4016, -0.207);
//
//StateSpaceController<2, 1, 1> controller(modelMotor);
//  controller.K = { -4.8697, -2.4895};
//  controller.Ki = {2.49};
  
//  controller.initialise();
//   y(0) = rpm;
//
//    controller.update(y, dt);
//
//    sinal_controle = int(controller.u(0));
//
//    int u_corrigido = constrain(sinal_controle, MIN_DUTYCYCLE, MAX_DUTYCYCLE);
