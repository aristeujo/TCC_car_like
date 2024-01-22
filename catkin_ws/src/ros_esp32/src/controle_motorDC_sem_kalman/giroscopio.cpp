#include "giroscopio.h"

MPU6050 mpu(Wire);

Giroscopio::Giroscopio(){}

Giroscopio::~Giroscopio(){}

void Giroscopio::setup_giro(){
  // Wire.begin();
  
  byte status = mpu.begin();
  Serial.print(F("MPU6050 status: "));
  Serial.println(status);
  while(status!=0){ } // stop everything if could not connect to MPU6050
  
  Serial.println(F("Calculating offsets, do not move MPU6050"));
  delay(1000);

  mpu.calcOffsets(); // gyro and accelero
  Serial.println("Done!\n");
};

void Giroscopio::update_mpu(){
  mpu.update();
};

void Giroscopio::get_data(){
//   this->accX = gToMpss(mpu.getAccX());
  this->angularVelocityZ = radians(mpu.getGyroZ());
//   this->angleZ = mpu.getAngleZ();
}

void Giroscopio::debug_data(){
    Serial.print(t/1000);
    Serial.print(",");
    Serial.print(accX);
    Serial.print(",");
    Serial.print(angularVelocityZ);
    Serial.print(",");
    Serial.println(velocidade_X);

};

float Giroscopio::estima_velocidade_X(float aceleracao){

    if(i_X == 1) {
      integral_aproximada_X = integral_aproximada_X + aceleracao; 
      i_X = 2;
    } 
    if(i_X == 2){
      integral_aproximada_X = integral_aproximada_X + 4 * aceleracao;
      i_X = 3;
    }
        
    else { 
      integral_aproximada_X = integral_aproximada_X + 2 * aceleracao;
      i_X = 2;
  }

  // Condição para considerar  que o carro está parado
  if(abs(aceleracao) < offsetParado){
    flag_X += 1;
    if(flag_X == 4){
      integral_aproximada_X = 0;
      i_X = 1;
      flag_X = 0;
    }
  }

  else{
    flag_X = 0;
  }

  float h = taxaDeAmostragem/1000;
  float velocidade_estimada_X = (h / 3) * integral_aproximada_X;

return velocidade_estimada_X;
};


float Giroscopio::gToMpss(float acc){
  return 9.80665*acc;
};
