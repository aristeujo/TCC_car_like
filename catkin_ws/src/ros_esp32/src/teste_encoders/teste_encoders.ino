#include "AS5600.h"
#include "Wire.h"
#include "encoder.h"
#include "motorDC.h"

MotorDC motor(19, 18, 4);

AS5600 as5600;   //  use default Wire

unsigned long timer_prbs = 0;
long previousMillis = 0;
unsigned long intervalo = 1000;

void setup()
{
  Serial.begin(115200);

  Serial.println(__FILE__);
  Serial.print("AS5600_LIB_VERSION: ");
  Serial.println(AS5600_LIB_VERSION);

  Wire.begin();

  as5600.begin(4);  //  set direction pin.
  as5600.setDirection(AS5600_CLOCK_WISE);  //  default, just be explicit.

  Serial.println(as5600.getAddress());

  // as5600.setAddress(0x40);  //  AS5600L only

  int b = as5600.isConnected();
  Serial.print("Connect: ");
  Serial.println(b);

  setEncoder();
  delay(1000);
}

void loop()
{

  if((millis() - timer_prbs)>=100){
  //  Serial.print("\ta = ");
  //  Serial.print(as5600.readAngle());
  Serial.print("\tω = ");
  Serial.println(as5600.getAngularSpeed(AS5600_MODE_RPM));
//  delay(100);
  motor.motorSpeed(200, FORWARD);
  calculoVelocidade(100);
  timer_prbs = millis();
 }
}


//  -- END OF FILE --
