#include "MPU6050Handler.h"

MPU6050Handler::MPU6050Handler(TwoWire &wire, SemaphoreHandle_t &mutex) : mpu(wire), i2cMutex(mutex) {}

MPU6050Handler::~MPU6050Handler() {}

bool MPU6050Handler::initialize() {
    if (xSemaphoreTake(i2cMutex, portMAX_DELAY)) {
        byte status = mpu.begin();
        xSemaphoreGive(i2cMutex);

        if (status != 0) {
            Serial.println("Failed to initialize MPU6050!");
            return false;
        }

        Serial.println("MPU6050 initialized successfully.");
        mpu.calcOffsets(); // Calibra o sensor
        return true;
    }
    return false;
}

void MPU6050Handler::update() {
    if (xSemaphoreTake(i2cMutex, portMAX_DELAY)) {
        mpu.update();

        mpuData.gyroZ = mpu.getGyroZ();
        xSemaphoreGive(i2cMutex);
    }
}

MPUData MPU6050Handler::getData() {
    return mpuData;
}
