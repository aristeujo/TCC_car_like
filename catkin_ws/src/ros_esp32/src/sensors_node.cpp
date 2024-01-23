#include "ros/ros.h"
#include "my_project_msgs/Sensors.h"
#include "nav_msgs/Odometry.h"

class Sensors_listener
{
private:
    const char *topic_sub = "/sensors_values";
    float rpm_eixo;
    float rpm_as5600_R;
    float rpm_as5600_L;

    ros::Subscriber sub_sensors;

public:
    Sensors_listener(ros::NodeHandle *nh);
    ~Sensors_listener();
    void sensorsCallback(const my_project_msgs::Sensors &msg);
};

Sensors_listener::Sensors_listener(ros::NodeHandle *nh)
{   
    sub_sensors = nh->subscribe(topic_sub, 100, &Sensors_listener::sensorsCallback, this);

}

Sensors_listener::~Sensors_listener()
{
}

void Sensors_listener::sensorsCallback(const my_project_msgs::Sensors &msg){

    this->rpm_eixo = msg.encoder_eixo;
    this->rpm_as5600_L = msg.encoder_as5600_L;
    this->rpm_as5600_R = msg.encoder_as5600_R;

    ROS_INFO("Eixo:%.2f AS5600_L:%.2f AS5600_R:%.2f", this->rpm_eixo, this->rpm_as5600_L, this->rpm_as5600_R);
}


int main(int argc,char **argv){
    ros::init(argc, argv, "sensors_node");
    ros::NodeHandle nh;

    Sensors_listener sensors = Sensors_listener(&nh);

    ros::spin();

    return 0;
}