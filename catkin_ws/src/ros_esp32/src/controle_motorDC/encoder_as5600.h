#ifndef ENCODER_AS5600_H
#define ENCODER_AS5600_H

#include <Arduino.h>
#include "AS5600.h"
#include "Wire.h"

class Encoder {
private:
    float rpm_as5600 = 0.0;
    SemaphoreHandle_t &i2cMutex;

public:
    Encoder(SemaphoreHandle_t &mutex);
    ~Encoder();

    void setEncoder_AS5600(AS5600 &obj, int SDA_pin, int SCL_pin, int direction_pin, TwoWire &I2C_obj);
    float getRPM_AS5600(AS5600 &obj);
};

#endif
