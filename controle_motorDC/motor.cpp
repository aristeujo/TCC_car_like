#include "motor.h"

Servo servo;

Motor::Motor(int motorPin1, int motorPin2, int enablePin, int servoPin)
{
    this->motorPin1 = motorPin1;
    this->motorPin2 = motorPin2;
    this->enablePin = enablePin;
    this->servoPin = servoPin;
}

Motor::~Motor()
{
}

void Motor::initMotor(){
  pinMode(this->motorPin1, OUTPUT);
  pinMode(this->motorPin2, OUTPUT);
  pinMode(this->enablePin, OUTPUT);

  ledcSetup(this->pwmChannel, this->freq, this->resolution);
  ledcAttachPin(this->enablePin, this->pwmChannel);

  servo.setPeriodHertz(50);  
  servo.attach(this->servoPin, 500, 2400); 
};

void Motor::motorSpeed(int velocidade, int sentido) {

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

void Motor::setAngle(int angle){
  servo.write(angle);
};
