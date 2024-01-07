#include "encoder.h"

#define ENC_IN_A 12 // Fio verde
#define ENC_IN_B 13 // Fio Amarelo

const int sensor_rpm_D = 36;
const int sensor_rpm_E = 34;

boolean direcao = true;

int pulsos_roda = 0;
volatile long pulsos_E;
volatile long pulsos_D;

const int ENC_COUNT_REV = 375;
unsigned int pulsos_por_volta_D = 45;
unsigned int pulsos_por_volta_E = 45;

// --- Variáveis Globais --- 
float rpm = 0;
float rpm_E = 0;
float rpm_D = 0;

void setEncoder(){
  pinMode(ENC_IN_A , INPUT_PULLUP);
  pinMode(ENC_IN_B , INPUT);
  // pinMode(sensor_rpm_D, INPUT_PULLUP);
  // pinMode(sensor_rpm_E, INPUT_PULLUP);
  // attachInterrupt(digitalPinToInterrupt(sensor_rpm_D), contador_D, FALLING);
  // attachInterrupt(digitalPinToInterrupt(sensor_rpm_E), contador_E, FALLING); 
  attachInterrupt(digitalPinToInterrupt(ENC_IN_A), roda_contador, RISING);

  // pulsos_D = 0;
  // pulsos_E = 0;
};

void calculoVelocidade(unsigned long intervalo) {

    rpm = (pulsos_roda*(60.0*1000.0)/(intervalo*ENC_COUNT_REV));
    // rpm = pulsos_roda;
    
    // rpm_D = (60*1000*pulsos_D) / (intervalo*pulsos_por_volta_D*2);
    // rpm_E = (60*1000*pulsos_E) / (intervalo*pulsos_por_volta_E*2);

    // pulsos_E = 0;
    // pulsos_D = 0;
    pulsos_roda = 0;

    //Habilita interrupcao
    // attachInterrupt(digitalPinToInterrupt(sensor_rpm_D), contador_D, FALLING);
    // attachInterrupt(digitalPinToInterrupt(sensor_rpm_E), contador_E, FALLING);
      
};

void roda_contador(){
  // Lê o valor do encoder da roda direita
  int val = digitalRead(ENC_IN_B);

  if (val == LOW) {
    direcao = true; // Trás
  }
  else {
    direcao = false; // Frente
  }

  if (direcao) {
    pulsos_roda++;
  }
  else {
    pulsos_roda--;
  }
};

// // --- Interrupção ---
// void contador_D()
// {
//   //Incrementa contador
//   pulsos_D++;
// };

// // --- Interrupção ---
// void contador_E()
// {
//   //Incrementa contador
//   pulsos_E++;
// };
