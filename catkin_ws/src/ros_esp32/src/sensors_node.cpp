#include "ros/ros.h"
#include <tf/transform_broadcaster.h>
#include "my_project_msgs/Sensors.h"
#include <nav_msgs/Odometry.h>
#include <math.h>

class Sensors_listener
{
private:
    //ROS parameters
    double wheelbase_ = 0.160143;
    double wheelRadius_ = 0.0335;

    const char *topic_sub_ = "/sensors_values";
    float rpm_eixo_;
    float rpm_as5600_R_;
    float rpm_as5600_L_;
    float angularVelocityZ_;

    double vL_, vR_;

    //odom state
    double x_, y_, yaw_, theta_, theta_dot_;

    ros::Subscriber sub_sensors_;
    ros::Publisher odom_pub_;
    tf::TransformBroadcaster odom_broadcaster_;
    ros::Time current_time_, last_time_;

public:
    Sensors_listener(ros::NodeHandle *nh);
    void sensorsCallback(const my_project_msgs::Sensors &msg);
    void odometry_calc();
};

Sensors_listener::Sensors_listener(ros::NodeHandle *nh)
{       
    current_time_ = ros::Time::now();
    last_time_ = ros::Time::now();
    sub_sensors_ = nh->subscribe(topic_sub_, 100, &Sensors_listener::sensorsCallback, this);
    odom_pub_ = nh->advertise<nav_msgs::Odometry>("odom", 100);
    
}

void Sensors_listener::odometry_calc(){

    // calc elapsed time
    current_time_ = ros::Time::now();
    // double dt = (current_time_ - last_time_).toSec();
    double dt = 0.1;

    // Convert rpm to m/s
    vL_ = (2*M_PI*rpm_as5600_L_*wheelRadius_)/60;;
    vR_ = (2*M_PI*rpm_as5600_R_*wheelRadius_)/60;

    double current_speed = (vL_+vR_)/2;
    
    // double x_dot = current_speed * cos(theta_);
    // double y_dot = current_speed * sin(theta_);

    double x_dot = current_speed * cos(yaw_);
    double y_dot = current_speed * sin(yaw_);

    // odometry estimation
    x_ += x_dot*dt;
    y_ += y_dot*dt;
    theta_ += (vR_ - vL_)/wheelbase_;
    
    yaw_ += angularVelocityZ_*dt;

    // abs(theta_) >= 2*M_PI ? 0.0 : theta_;

    if(theta_ > M_PI) {theta_ -= 2*M_PI;}
    else if(theta_ < -M_PI) {theta_ += 2*M_PI;}

    theta_dot_ = (current_speed * tan(theta_)) / wheelbase_;

    ROS_INFO("X: %.2f || Y: %.2f || Theta: %.2f || Yaw_MPU: %.2f", x_, y_, theta_, yaw_);

    // Create Quartenion from Yaw angle
    geometry_msgs::Quaternion odom_quat = tf::createQuaternionMsgFromYaw(yaw_);

    // publish transform over tf
    geometry_msgs::TransformStamped odom_tf;
    odom_tf.header.stamp = current_time_;
    odom_tf.header.frame_id = "odom";
    odom_tf.child_frame_id = "base_link";

    odom_tf.transform.translation.x = x_;
    odom_tf.transform.translation.y = y_;
    odom_tf.transform.translation.z = 0.0;
    odom_tf.transform.rotation = odom_quat;

    // send transform
    odom_broadcaster_.sendTransform(odom_tf);

    // make odom message
    nav_msgs::Odometry odom;
    odom.header.stamp = current_time_;
    odom.header.frame_id = "odom";

    // set the position
    odom.pose.pose.position.x = x_;
    odom.pose.pose.position.y = y_;
    odom.pose.pose.position.z = 0.0;
    odom.pose.pose.orientation = odom_quat;

    // set the velocity
    odom.child_frame_id = "base_link";
    odom.twist.twist.linear.x = x_dot;
    odom.twist.twist.linear.y = y_dot;
    odom.twist.twist.angular.z = angularVelocityZ_;

    // Publish the odometry message
    odom_pub_.publish(odom);

    last_time_ = current_time_;

}

void Sensors_listener::sensorsCallback(const my_project_msgs::Sensors &msg){

    this->rpm_eixo_ = msg.encoder_eixo;
    this->rpm_as5600_L_ = msg.encoder_as5600_L;
    this->rpm_as5600_R_ = msg.encoder_as5600_R;
    this->angularVelocityZ_ = msg.Yaw;

    // ROS_INFO("Eixo:%.2f AS5600_L:%.2f AS5600_R:%.2f", this->rpm_eixo_, this->rpm_as5600_L_, this->rpm_as5600_R_);
}


int main(int argc,char **argv){
    ros::init(argc, argv, "sensors_node");
    ros::NodeHandle nh;

    Sensors_listener sensors = Sensors_listener(&nh);

    ros::Rate r(10.0);
    while(nh.ok()){

        ros::spinOnce();

        sensors.odometry_calc();

        r.sleep();
    }

    return 0;
}