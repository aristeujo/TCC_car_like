#include "ros/ros.h"
#include <tf/transform_broadcaster.h>
#include "my_project_msgs/Sensors.h"
#include <nav_msgs/Odometry.h>
#include <math.h>

class Sensors_listener
{
private:
    //ROS parameters
    double wheelbase_;
    double wheelRadius_;

    const char *topic_sub_ = "/sensors_values";
    float rpm_eixo_;
    float rpm_as5600_R_;
    float rpm_as5600_L_;

    double vL_, vR_;

    //odom state
    double x_, y_, yaw_, theta_;

    ros::Subscriber sub_sensors_;
    ros::Publisher odom_pub_;
    tf::TransformBroadcaster odom_broadcaster_;
    ros::Time current_time_, last_time_;

public:
    Sensors_listener(ros::NodeHandle *nh);
    ~Sensors_listener();
    void sensorsCallback(const my_project_msgs::Sensors &msg);
    void odometry_calc();
};

Sensors_listener::Sensors_listener(ros::NodeHandle *nh)
{   
    sub_sensors_ = nh->subscribe(topic_sub_, 100, &Sensors_listener::sensorsCallback, this);

}

void Sensors_listener::odometry_calc(){

    // Convert rpm to m/s
    vL_ = (2*M_PI*rpm_as5600_L_*wheelRadius_)/60;;
    vR_ = (2*M_PI*rpm_as5600_R_*wheelRadius_)/60;

    // calc elapsed time
    current_time_ = ros::Time::now();

    double dt = (current_time_ - last_time_).toSec();

    double current_speed = (vL_+vR_)/2;
    
    double x_dot = current_speed * cos(theta_);
    double y_dot = current_speed * sin(theta_);

    // odometry estimation
    x_ += x_dot*dt;
    y_ += y_dot*dt;
    theta_ += (vR_ - vL_)/wheelbase_;

    last_time_ = current_time_;
}

void Sensors_listener::sensorsCallback(const my_project_msgs::Sensors &msg){

    this->rpm_eixo_ = msg.encoder_eixo;
    this->rpm_as5600_L_ = msg.encoder_as5600_L;
    this->rpm_as5600_R_ = msg.encoder_as5600_R;

    ROS_INFO("Eixo:%.2f AS5600_L:%.2f AS5600_R:%.2f", this->rpm_eixo_, this->rpm_as5600_L_, this->rpm_as5600_R_);
}


int main(int argc,char **argv){
    ros::init(argc, argv, "sensors_node");
    ros::NodeHandle nh;

    Sensors_listener sensors = Sensors_listener(&nh);

    ros::spin();

    return 0;
}