#ifndef MOTORDC_H_
#define MOTORDC_H_

#include <Arduino.h>

#define FORWARD 1
#define BACKWARD 0
#define STOP 2

class MotorDC
{
private:
    const int freq = 5000;
    const int pwmChannel = 2;
    const int resolution = 8;

    int motorPin1 = 0;
    int motorPin2 = 0;
    int enablePin = 0;

public:
    MotorDC(int motorPin1, int motorPin2, int enablePin);
    ~MotorDC();

    void initMotor();
    void motorSpeed(int velocidade, int sentido);
};

#endif
