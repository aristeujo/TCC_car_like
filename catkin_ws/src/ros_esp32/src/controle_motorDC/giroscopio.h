#ifndef GIROSCOPIO_H_
#define GIROSCOPIO_H_

#include "Wire.h"
#include <MPU6050_light.h>
#include <math.h>

class Giroscopio
{
private:
    unsigned long timer = 0;
    float taxaDeAmostragem = 50;
    float integral_aproximada_X = 0;
    float t = 0;
    int i_X = 1;
    float offsetParado = 0.1;
    float vel_offsetParado = 0.01;
    int flag_X = 0;
    float accX = 0;
    int j = 1;


public:
    Giroscopio();
    ~Giroscopio();

    float velocidade_X = 0;
    float angularVelocityZ = 0;
    float angleZ = 0;

    void setup_giro();
    void get_data_mpu();
    void debug_data();
    float estima_velocidade_X(float aceleracao);
    float gToMpss(float acc);
};

#endif
