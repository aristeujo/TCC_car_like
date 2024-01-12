#define ROSSERIAL_ARDUINO_TCP
#include "WiFi.h"
#include <ros.h>
#include <geometry_msgs/Twist.h>
#include<my_project_msgs/Sensors.h>

void setupWiFi();
void cmdVel_to_pwm_cb( const geometry_msgs::Twist &velocity_msg);

IPAddress server(192, 168, 0, 30);
uint16_t serverPort = 11411;
const char*  ssid = "Seixas_Net";
const char*  password = "Mayum647";

ros::NodeHandle  nh;


my_project_msgs::Sensors msg;
ros::Publisher chatter("/sensors_values", &msg);
ros::Subscriber<geometry_msgs::Twist> sub("/cmd_vel", &cmdVel_to_pwm_cb );


void setup()
{
  Serial.begin(57600);
  pinMode(2, OUTPUT);
  setupWiFi();
  nh.getHardware()->setConnection(server, serverPort);
  nh.initNode();
  nh.advertise(chatter);
  nh.subscribe(sub);

  msg.encoder_eixo = 150;
  msg.encoder_as5600_L = 100;
  msg.encoder_as5600_R = 110;
  Serial.println("Fim do setup");
  delay(2000);
}

void loop()
{
  chatter.publish(&msg);
  nh.spinOnce();
  delay(100);
}

void setupWiFi()
{  
   WiFi.begin(ssid, password);
   while (WiFi.status() != WL_CONNECTED) { delay(500);Serial.print("."); }
   Serial.print("SSID: ");
   Serial.println(WiFi.SSID());
   Serial.print("IP:   ");
   Serial.println(WiFi.localIP());
   digitalWrite(2, HIGH);

}

void cmdVel_to_pwm_cb( const geometry_msgs::Twist &velocity_msg){

    float right_wheel = (velocity_msg.linear.x + velocity_msg.angular.z ) / 2 ;
    float left_wheel = (velocity_msg.linear.x - velocity_msg.angular.z ) /2 ;

    Serial.print(left_wheel);Serial.print(" / ");Serial.println(right_wheel);

}
