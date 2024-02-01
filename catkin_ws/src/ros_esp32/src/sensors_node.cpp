#include "ros/ros.h"
#include <std_msgs/String.h>
#include <ackermann_msgs/AckermannDriveStamped.h>
#include <tf/transform_broadcaster.h>
#include "my_project_msgs/Sensors.h"
#include "my_project_msgs/Command_ackermann.h"
#include <nav_msgs/Odometry.h>
#include <math.h>

class Sensors_listener
{
private:
    //ROS parameters in m
    double wheelbase_;
    double wheelRadius_;
    double initial_x_;
    double initial_y_;
    double initial_yaw_;

    const char *topic_sub_ = "/sensors_values";
    float rpm_eixo_;
    float rpm_as5600_R_;
    float rpm_as5600_L_;
    float angularVelocityZ_;

    // path coeficients
    double A, B, C;

    // ackermann msgs commands
    double linear_speed_ = 0.0, steering_angle_ = 0.0, last_steering_angle = 0.0;

    // converted ackermann commands
    double rpm_;
    double cruising_speed, max_speed;
    double motor_setpoint;
    double beta = 1.82;
    double angle_servo;
    double min_angle_servo;
    double max_angle_servo;
    double min_angle_servo_radians;
    double max_angle_servo_radians;

    // controller gains
    double K_1, K_2;
    
    // Wheel velocities in mm/s
    double vL_, vR_;

    //odom state
    double x_, y_, yaw_, yaw_mpu_, yaw_est_, theta_, current_angular_velocity;
    double current_speed = 0.0, x_dot = 0.0, y_dot = 0.0;

    // Time Test
    double time;

    //estimated integral
    double integral_approx_ = 0.0, i_ = 1.0;

    int flag  = 0;

    ros::Subscriber sub_sensors_;
    ros::Publisher odom_pub_;
    tf::TransformBroadcaster odom_broadcaster_;
    ros::Time current_time_;
    ros::Subscriber car_commands_;
    ros::Publisher car_commands_pub_;
    ros::Subscriber iniTeste;
    ros::Timer timerEnd;

public:
    Sensors_listener(ros::NodeHandle *nh);
    void sensorsCallback(const my_project_msgs::Sensors &msg);
    void ackermannCallback(const ackermann_msgs::AckermannDriveStamped &msg);
    void initCallback(const std_msgs::String &msg);
    void timerEndCallback(const ros::TimerEvent &event);
    double estimated_integral(double state_dot);
    void odometry_calc();
    void sendAckerCommands(double linear_speed, double steering_angle);
    void saturate(double* input, double lowerLimit, double upperLimit);
    void range(double *input);
    double calcDistance(double A, double B, double C, double x0, double y0);
    void controller(double rpm);
};

Sensors_listener::Sensors_listener(ros::NodeHandle *nh)
{       
    nh->getParam("wheelBase", wheelbase_);
    nh->getParam("wheelRadius", wheelRadius_);
    nh->getParam("offset_angle_servo", angle_servo);
    if(nh->getParam("min_angle_servo", min_angle_servo)){
        min_angle_servo_radians = min_angle_servo*(M_PI/180);
    }
    if(nh->getParam("max_angle_servo", max_angle_servo)){
        max_angle_servo_radians = max_angle_servo*(M_PI/180);
    }
    nh->getParam("max_speed", max_speed);
    nh->getParam("K_1", K_1);
    nh->getParam("K_2", K_2);
    nh->getParam("A", A);
    nh->getParam("B", B);
    nh->getParam("C", C);

    nh->getParam("/sensors_node/x_initial", initial_x_);
    nh->getParam("/sensors_node/y_initial", initial_y_);
    nh->getParam("/sensors_node/yaw_initial", initial_yaw_);
    if(nh->getParam("/sensors_node/cruising_speed", cruising_speed)){
        if(cruising_speed > max_speed){
            cruising_speed = max_speed;
        }

        motor_setpoint = 285.0536294*cruising_speed*beta; 
    }
    nh->getParam("/sensors_node/time", time);

    x_ = initial_x_;
    y_ = initial_y_;
    yaw_ = initial_yaw_;

    current_time_ = ros::Time::now();
    sub_sensors_ = nh->subscribe(topic_sub_, 100, &Sensors_listener::sensorsCallback, this);
    odom_pub_ = nh->advertise<nav_msgs::Odometry>("odom", 100);
    car_commands_ = nh->subscribe("/ackermann_cmd", 100, &Sensors_listener::ackermannCallback, this);
    car_commands_pub_ = nh->advertise<my_project_msgs::Command_ackermann>("/cmd_car", 100); 
    iniTeste = nh->subscribe("/iniTeste", 100, &Sensors_listener::initCallback, this);
    // timerEnd = nh->createTimer(ros::Duration(time), &Sensors_listener::timerEndCallback, this);
}

void Sensors_listener::odometry_calc(){

    // calc elapsed time
    current_time_ = ros::Time::now();
    double dt = 0.1;

    if(flag == 1){
    // Convert rpm to m/s
    vL_ = (2*M_PI*rpm_as5600_L_*wheelRadius_)/60;
    vR_ = (2*M_PI*rpm_as5600_R_*wheelRadius_)/60;

    current_speed = (vL_+vR_)/2;

    x_dot = current_speed * cos(yaw_);
    y_dot = current_speed * sin(yaw_);

    // odometry estimation  
    x_ += x_dot*dt;
    y_ += y_dot*dt;

    if(steering_angle_ != 0){
        current_angular_velocity = current_speed * tan(steering_angle_) / wheelbase_;
        theta_ += current_angular_velocity*dt;
    }

    // abs(theta_) >= 2*M_PI ? 0.0 : theta_;
    if(theta_ > M_PI) {theta_ -= 2*M_PI;}
    else if(theta_ < -M_PI) {theta_ += 2*M_PI;}
    
    yaw_mpu_ += angularVelocityZ_*dt;
    // yaw_est_ = estimated_integral(angularVelocityZ_);

    // combinated Yaw

    if(steering_angle_ != 0){
        yaw_ = yaw_mpu_*0.7261 + theta_*0.2739;
        // yaw_ = yaw_mpu_ + 0.2739*(theta_ - yaw_mpu_);
    }
    else{
        yaw_ = yaw_mpu_;
    }
    yaw_ += initial_yaw_;

    if(yaw_ > M_PI) {yaw_ -= 2*M_PI;}
    else if(yaw_ < -M_PI) {yaw_ += 2*M_PI;}    

    // range(&yaw_);
    // range(&theta_);

    controller(motor_setpoint);
    }

    // ROS_INFO("Theta: %.2f  ||    Yaw_mpu: %.2f    || Yaw_comb: %.2f", theta_, yaw_est_, yaw_);
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
}

// ALPHA = 5.5

void Sensors_listener::saturate(double* input, double lowerLimit, double upperLimit){
  if(*input < lowerLimit) *input = lowerLimit;
  if(*input > upperLimit) *input = upperLimit;
}

void Sensors_listener::range(double *input){
    if(*input > M_PI) {*input -= 2*M_PI;}
    if(*input < -M_PI) {*input += 2*M_PI;}    
}

double Sensors_listener::calcDistance(double A, double B, double C, double x0, double y0){
    double distancia = abs(A * x0 + B * y0 + C) / sqrt(A*A + B*B);

    return distancia;
}

void Sensors_listener::controller(double rpm){
    double e = calcDistance(A, B, C, x_, y_);
    double psi = yaw_ - atan(1);

    if(y_ < x_) e = (-1)*e;

    // control signal
    double u = K_1*e + K_2*psi;
    saturate(&u, min_angle_servo_radians, max_angle_servo_radians);
    ROS_INFO("u: %.2f", u);;

    angle_servo = 89 - (180/M_PI)*u;

    // send r and u to ESP32
    sendAckerCommands(rpm, angle_servo);
}

void Sensors_listener::sendAckerCommands(double linear_speed, double steering_angle){
    my_project_msgs::Command_ackermann msg_cmd;
    msg_cmd.rpm = linear_speed;
    msg_cmd.servo_angle = steering_angle;

    car_commands_pub_.publish(msg_cmd);
}

void Sensors_listener::sensorsCallback(const my_project_msgs::Sensors &msg){

    this->rpm_eixo_ = msg.encoder_eixo;
    this->rpm_as5600_L_ = msg.encoder_as5600_L;
    this->rpm_as5600_R_ = msg.encoder_as5600_R;
    this->angularVelocityZ_ = msg.angularVelocity;

    odometry_calc();

    // ROS_INFO("Eixo:%.2f AS5600_L:%.2f AS5600_R:%.2f", this->rpm_eixo_, this->rpm_as5600_L_, this->rpm_as5600_R_);
}

void Sensors_listener::ackermannCallback(const ackermann_msgs::AckermannDriveStamped &msg){

    linear_speed_ = msg.drive.speed;
    steering_angle_ = msg.drive.steering_angle;

    // ROS_INFO("linear_vel:%.2f steering_angle:%.2f", linear_speed_, steering_angle_);

    // RPM setpoint

    // if(yaw__1 <= -1.4 && yaw__1 > -3.14) {
    //     rpm = 0;
    // }

    // else{
    rpm_ = (60/2*M_PI*wheelRadius_)*(linear_speed_)*100;
    // }
        
     
    angle_servo = 89 - (180/M_PI)*steering_angle_;
    saturate(&angle_servo, 69, 109);

    sendAckerCommands(rpm_, angle_servo);

    // ROS_INFO("rpm:%.2f angle_servo:%.2f", rpm, angle_servo);
}

void Sensors_listener::initCallback(const std_msgs::String &msg){
    if(msg.data == "start"){
        ros::NodeHandle nh;
        timerEnd = nh.createTimer(ros::Duration(time), &Sensors_listener::timerEndCallback, this);
        ROS_INFO("Teste iniciado");
        flag = 1;
    }  
}

void Sensors_listener::timerEndCallback(const ros::TimerEvent &event){
    if(flag == 1){
        ROS_INFO("Teste finalizado");
        sendAckerCommands(0.0, 89.0);
        flag = 2;
    }

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

int main(int argc,char **argv){
    ros::init(argc, argv, "sensors_node");
    ros::NodeHandle nh;

    Sensors_listener sensors = Sensors_listener(&nh);

    ros::spin();

    return 0;
}