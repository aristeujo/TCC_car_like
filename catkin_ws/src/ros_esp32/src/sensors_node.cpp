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
    double x_,y_, yaw_, yaw__1, yaw_est_, theta_, theta_dot_;

    //estimated integral
    double integral_approx_ = 0.0, i_ = 1.0;

    ros::Subscriber sub_sensors_;
    ros::Publisher odom_pub_;
    tf::TransformBroadcaster odom_broadcaster_;
    ros::Time current_time_, last_time_;

public:
    Sensors_listener(ros::NodeHandle *nh);
    void sensorsCallback(const my_project_msgs::Sensors &msg);
    double estimated_integral(double state_dot);
    void odometry_calc();
};

Sensors_listener::Sensors_listener(ros::NodeHandle *nh)
{       
    current_time_ = ros::Time::now();
    last_time_ = ros::Time::now();
    sub_sensors_ = nh->subscribe(topic_sub_, 100, &Sensors_listener::sensorsCallback, this);
    odom_pub_ = nh->advertise<nav_msgs::Odometry>("odom", 100);
    
}

double Sensors_listener::estimated_integral(double state_dot){

    if(i_ == 1) {
      integral_approx_ = integral_approx_ + state_dot; 
      i_ = 2;
    } 
    if(i_ == 2){
      integral_approx_ = integral_approx_ + 4 * state_dot;
      i_ = 3;
    }
        
    else { 
      integral_approx_ = integral_approx_ + 2 * state_dot;
      i_ = 2;
  }

  double h = 0.1;
  double integral_est = (h / 3) * integral_approx_;

return integral_est;
};

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
    
    yaw__1 += angularVelocityZ_*dt;
    yaw_est_ = estimated_integral(angularVelocityZ_);

    // combinated Yaw
    yaw_ = yaw__1*0.4 + yaw_est_*0.6;

    if(yaw_ > M_PI) {yaw_ -= 2*M_PI;}
    else if(yaw_ < -M_PI) {yaw_ += 2*M_PI;}    

    // abs(theta_) >= 2*M_PI ? 0.0 : theta_;
    // if(theta_ > M_PI) {theta_ -= 2*M_PI;}
    // else if(theta_ < -M_PI) {theta_ += 2*M_PI;}

    // theta_dot_ = (current_speed * tan(theta_)) / wheelbase_;

    ROS_INFO("X: %.2f || Y: %.2f || Yaw: %.2f  || X_dot: %.2f || Y_dot: %.2f", x_, y_, yaw_, x_dot, y_dot);
    // ROS_INFO("X: %.2f || Y: %.2f || Theta: %.4f || Yaw_MPU: %.4f || Yaw_est: %.4f", x_, y_, yaw_, yaw__1, yaw_est_);

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

    // last_time_ = current_time_;

    // last_time_ = ros::Time::now();

    // time in seconds
    // double delta_time_  = (last_time_ - current_time_).toSec();

    // ROS_INFO("Tempo: %.6f", delta_time_);

}

void Sensors_listener::sensorsCallback(const my_project_msgs::Sensors &msg){

    this->rpm_eixo_ = msg.encoder_eixo;
    this->rpm_as5600_L_ = msg.encoder_as5600_L;
    this->rpm_as5600_R_ = msg.encoder_as5600_R;
    this->angularVelocityZ_ = msg.Yaw;

    odometry_calc();

    // ROS_INFO("Eixo:%.2f AS5600_L:%.2f AS5600_R:%.2f", this->rpm_eixo_, this->rpm_as5600_L_, this->rpm_as5600_R_);
}


int main(int argc,char **argv){
    ros::init(argc, argv, "sensors_node");
    ros::NodeHandle nh;

    Sensors_listener sensors = Sensors_listener(&nh);

    ros::spin();

    return 0;
}