#ifndef ENCODER_H
#define ENCODER_H

#include <Arduino.h>

extern float rpm;
extern float rpm_D;
extern float rpm_E;
extern int pulsos_roda;

void calculoVelocidade(unsigned long intervalo);
void roda_contador();
void setEncoder();
// void contador_D();
// void contador_E();

#endif
