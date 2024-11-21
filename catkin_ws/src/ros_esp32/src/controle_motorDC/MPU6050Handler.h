#ifndef MPU6050HANDLER_H
#define MPU6050HANDLER_H

#include <Wire.h>
#include <MPU6050_light.h>

struct MPUData {
    float accX, accY, accZ;
    float gyroX, gyroY, gyroZ;
    float temperature;
};

class MPU6050Handler {
private:
    MPU6050 mpu;
    SemaphoreHandle_t &i2cMutex; // Mutex para sincronizar o barramento I2C
    MPUData mpuData;

public:
    MPU6050Handler(TwoWire &wire, SemaphoreHandle_t &mutex);
    ~MPU6050Handler();

    bool initialize();
    void update();
    MPUData getData();
};

#endif
