#include "motorDC.h"

MotorDC::MotorDC(int motorPin1, int motorPin2, int enablePin)
{
    this->motorPin1 = motorPin1;
    this->motorPin2 = motorPin2;
    this->enablePin = enablePin;
}

MotorDC::~MotorDC()
{
}

void MotorDC::initMotor(){
  
}

void MotorDC::motorSpeed(int velocidade, int sentido) {

  switch (sentido) {
    case 0: //Forward
      digitalWrite(this->motorPin1, HIGH);
      digitalWrite(this->motorPin2, LOW);
      ledcWrite(this->pwmChannel, velocidade);
      break;

    case 1: //BackWard
      digitalWrite(this->motorPin1, LOW);
      digitalWrite(this->motorPin2, HIGH);
      ledcWrite(this->pwmChannel, velocidade);
      break;

    case 2: // Stop
      digitalWrite(this->motorPin1, LOW);
      digitalWrite(this->motorPin2, LOW);
      ledcWrite(this->pwmChannel, velocidade);
      break;

    default:
      break;
  }
};