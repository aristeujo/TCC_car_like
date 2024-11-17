#ifndef GIROSCOPIO_H_
#define GIROSCOPIO_H_

#include <MPU6050_light.h>
#include <math.h>
#include <freertos/semphr.h>

class Giroscopio {
private:
    MPU6050 mpu;
    SemaphoreHandle_t i2cMutex;

    unsigned long timer = 0;
    float taxaDeAmostragem = 50;
    float integral_aproximada_X = 0;
    int i_X = 1;
    float offsetParado = 0.1;
    int flag_X = 0;
    float accX = 0;

public:
    float velocidade_X = 0;
    float angularVelocityZ = 0;
    float angleZ = 0;

    Giroscopio(TwoWire &wire, SemaphoreHandle_t &mutex);
    ~Giroscopio();

    void setup_giro();
    void update_mpu();
    void get_data();
    float estima_velocidade_X(float aceleracao);
    float gToMpss(float acc);
};

#endif
