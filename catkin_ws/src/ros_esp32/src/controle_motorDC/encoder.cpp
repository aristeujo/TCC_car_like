#include "encoder.h" 

Encoder::Encoder(){}

Encoder::~Encoder(){}

void Encoder::setEncoder_AS5600(AS5600 &obj, int SCL_pin, int SDA_pin, int direction_pin, TwoWire &I2C_obj){

    I2C_obj.begin(SCL_pin, SDA_pin);
    obj.begin(direction_pin);  //  set direction pin.
    obj.setDirection(AS5600_COUNTERCLOCK_WISE);  // default, just be explicit.

     int b = obj.isConnected();
     Serial.print("Connect: ");
     Serial.println(b);
};

float Encoder::getRPM_AS5600(AS5600 &obj){
    this->rpm_as5600 = obj.getAngularSpeed(AS5600_MODE_RPM);

    return this->rpm_as5600;
};

float Encoder::getRPM_MotorEixo(unsigned long intervalo){

    this->rpm = (this->pulsos_roda*(60.0*1000.0)/(intervalo*this->ENC_COUNT_REV));

    this->pulsos_roda = 0;

    return this->rpm;
};
