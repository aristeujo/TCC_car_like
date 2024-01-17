#ifndef ENCODER_H
#define ENCODER_H

#include <Arduino.h>
#include "AS5600.h"
#include "Wire.h"

class Encoder
{
private:
    const int ENC_COUNT_REV = 375;
    float rpm = 0.0;
    float rpm_as5600 = 0.0;

public:
    Encoder(/* args */);
    ~Encoder(); 

    void setEncoder_AS5600(AS5600 &obj, int SCL_pin, int SDA_pin, int direction_pin, TwoWire &I2C_obj);
    float getRPM_AS5600(AS5600 &obj);
    float getRPM_MotorEixo(unsigned long intervalo);

    int pulsos_roda;
    boolean direcao = true;
};


#endif
