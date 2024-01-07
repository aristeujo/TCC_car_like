#include "AS5600.h"
#include "Wire.h"
#include "encoder.h"

void motorSpeed(int velocidade, int sentido);

#define FORWARD 1
#define BACKWARD 0
#define STOP 2

const int freq = 5000;
const int pwmChannel = 2;
const int resolution = 8;

AS5600 as5600;   //  use default Wire

int motorPin1 = 19;
int motorPin2 = 18;
int enablePin = 4;

unsigned long timer_prbs = 0;
long previousMillis = 0;
unsigned long intervalo = 1000;

void setup()
{
  Serial.begin(115200);
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(enablePin, OUTPUT);

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
  ledcSetup(pwmChannel, freq, resolution);
  ledcAttachPin(enablePin, pwmChannel);

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
  motorSpeed(200, FORWARD);
  calculoVelocidade(100);
  timer_prbs = millis();
 }
}


void motorSpeed(int velocidade, int sentido) {

  switch (sentido) {
    case 0: //Forward
      digitalWrite(motorPin1, HIGH);
      digitalWrite(motorPin2, LOW);
      ledcWrite(pwmChannel, velocidade);
      break;

    case 1: //BackWard
      digitalWrite(motorPin1, LOW);
      digitalWrite(motorPin2, HIGH);
      ledcWrite(pwmChannel, velocidade);
      break;

    case 2: // Stop
      digitalWrite(motorPin1, LOW);
      digitalWrite(motorPin2, LOW);
      ledcWrite(pwmChannel, velocidade);
      break;

    default:
      break;
  }
};


//  -- END OF FILE --
