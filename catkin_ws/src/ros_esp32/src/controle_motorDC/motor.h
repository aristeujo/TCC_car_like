#ifndef MOTOR_H_
#define MOTOR_H_

#include <Arduino.h>
#include <ESP32Servo.h>

class Motor
{
private:
    const int freq = 5000;
    const int pwmChannel = 2;
    const int resolution = 8;

    int motorPin1 = 0;
    int motorPin2 = 0;
    int enablePin = 0;
    int servoPin = 0;

public:
    Motor(int motorPin1, int motorPin2, int enablePin, int servoPin);
    ~Motor();

    void initMotor();
    void motorSpeed(int velocidade, int sentido);
    void setAngle(int angle);

    int angulo_frente = 98;
};

#endif
