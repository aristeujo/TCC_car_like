#include "encoder_as5600.h"

Encoder::Encoder(SemaphoreHandle_t &mutex) : i2cMutex(mutex) {}

Encoder::~Encoder() {}

void Encoder::setEncoder_AS5600(AS5600 &obj, int SCL_pin, int SDA_pin, int direction_pin, TwoWire &I2C_obj) {
    if (xSemaphoreTake(i2cMutex, portMAX_DELAY)) {
        I2C_obj.begin(SCL_pin, SDA_pin);
        obj.begin(direction_pin);
        obj.setDirection(AS5600_COUNTERCLOCK_WISE);

        int isConnected = obj.isConnected();
        Serial.print("AS5600 Connected: ");
        Serial.println(isConnected);
        xSemaphoreGive(i2cMutex);
    }
}

float Encoder::getRPM_AS5600(AS5600 &obj) {
    if (xSemaphoreTake(i2cMutex, portMAX_DELAY)) {
        rpm_as5600 = obj.getAngularSpeed(AS5600_MODE_RPM);
        xSemaphoreGive(i2cMutex);
    }
    return rpm_as5600;
}
