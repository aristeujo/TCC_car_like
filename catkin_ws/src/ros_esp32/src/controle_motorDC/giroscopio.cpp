#include "giroscopio.h"

Giroscopio::Giroscopio(TwoWire &wire, SemaphoreHandle_t &mutex) : mpu(wire), i2cMutex(mutex) {}

Giroscopio::~Giroscopio() {}

void Giroscopio::setup_giro() {
    byte status = mpu.begin();
    if (status != 0) {
        Serial.print(F("MPU6050 status: "));
        Serial.println(status);
        while (status != 0) {}
    }
    Serial.println(F("Calculating offsets, do not move MPU6050"));
    delay(1000);
    mpu.calcOffsets();
    Serial.println("Done!");
}

void Giroscopio::update_mpu() {
    if (xSemaphoreTake(i2cMutex, portMAX_DELAY)) {
        mpu.update();
        xSemaphoreGive(i2cMutex);
    }
}

void Giroscopio::get_data() {
    if (xSemaphoreTake(i2cMutex, portMAX_DELAY)) {
        accX = gToMpss(mpu.getAccX());
        angularVelocityZ = radians(mpu.getGyroZ());
        angleZ = mpu.getAngleZ();
        xSemaphoreGive(i2cMutex);
    }
}

float Giroscopio::estima_velocidade_X(float aceleracao) {
    if (i_X == 1) {
        integral_aproximada_X += aceleracao;
        i_X = 2;
    } else if (i_X == 2) {
        integral_aproximada_X += 4 * aceleracao;
        i_X = 3;
    } else {
        integral_aproximada_X += 2 * aceleracao;
        i_X = 2;
    }

    if (abs(aceleracao) < offsetParado) {
        flag_X++;
        if (flag_X == 4) {
            integral_aproximada_X = 0;
            i_X = 1;
            flag_X = 0;
        }
    } else {
        flag_X = 0;
    }

    float h = taxaDeAmostragem / 1000;
    return (h / 3) * integral_aproximada_X;
}

float Giroscopio::gToMpss(float acc) {
    return 9.80665 * acc;
}
