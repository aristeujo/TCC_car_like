#include "kalmanFilter.h"
#include "stateSpaceMatrices.h"
#include "controller.h"
#include "kalmanFilter.h"
#include "motor.h"
#include "AS5600.h"
#include "encoder.h"

void roda_contador();

#define FORWARD 1
#define BACKWARD 0
#define STOP 2

#define ENC_IN_A 12 // Fio verde
#define ENC_IN_B 13 // Fio Amarelo

Motor motor(19,18,4,22);
Encoder encoder;

AS5600 as5600_0(&Wire);
AS5600 as5600_1(&Wire1);

KalmanFilter motorFilter(sysX.A, sysX.B, sysX.C, 3.5e-2, 1e-3);
Controller Controller({-4.8697, -2.4895}, {2.49});
//Controller Controller({-4.8697, -2.4895}, {0});

Matrix<2, 1> states = {0, 0};

float u = 0;

long previousMillis = 0;
unsigned long timer = 0;
unsigned long intervalo = 100;

int angulo_frente = 98;

const int potPin = 34;

Matrix<1> y;

void setup() {

  Serial.begin(115200);
  Wire.begin();
  motor.initMotor();

  pinMode(potPin, INPUT);  
  pinMode(ENC_IN_A , INPUT_PULLUP);
  pinMode(ENC_IN_B , INPUT);
  
  attachInterrupt(digitalPinToInterrupt(ENC_IN_A), roda_contador, RISING);

  encoder.setEncoder_AS5600(as5600_0, 23); 
  
  motor.motorSpeed(0, STOP);
  motor.setAngle(angulo_frente);
  Serial.println("End of Setup");

  delay(2000);
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
    timer = millis();
  }
}

void roda_contador(){
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