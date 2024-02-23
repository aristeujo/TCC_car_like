#include "ros/ros.h"
#include <std_msgs/String.h>
#include <ackermann_msgs/AckermannDriveStamped.h>
#include <tf/transform_broadcaster.h>
#include "my_project_msgs/Sensors.h"
#include "my_project_msgs/Command_ackermann.h"
#include "my_project_msgs/Data.h"
#include <nav_msgs/Odometry.h>
#include <math.h>


class CarLike_Control
{
private:
    // ROS parameters
    double wheelbase_;
    double wheelRadius_;
    double offset_angle_servo;
    double min_angle_servo;
    double max_angle_servo;
    double max_speed;
    double min_angle_servo_radians;
    double max_angle_servo_radians;

    // Controller gains
    double K_1, K_2;

    // Path coeficients
    double A, B, C;

    double initial_x_;
    double initial_y_;
    double initial_theta_;

    // Sensors message values
    const char *topic_sub_ = "/sensors_values";
    float rpm_eixo_;
    float rpm_as5600_R_;
    float rpm_as5600_L_;
    float angularVelocityZ_;

    // Lateral control states
    double e = 0.0, psi = 0.0;

    // Actuators command values
    double motor_setpoint = 0.0, angle_servo;

    // Ackermann message commands
    double linear_speed_ = 0.0, steering_angle_ = 0.0;

    // converted ackermann commands
    double rpm_;

    // Wheel velocities in mm/s
    double vL_, vR_;

    // Odometry variables
    double x_ = 0, y_, theta_odom_ = 0, theta_imu_, theta_, current_angular_velocity;
    double x_dot = 0.0, y_dot = 0.0, current_speed = 0.0;

    // Time Test
    double time;
    int flag  = 1;

    ros::Subscriber sub_sensors_;
    ros::Publisher odom_pub_;
    ros::Publisher data_pub_;
    tf::TransformBroadcaster odom_broadcaster_;
    ros::Time current_time_;
    ros::Subscriber car_commands_;
    ros::Publisher car_commands_pub_;
    ros::Subscriber iniTeste;
    ros::Timer timerEnd;

public:
    CarLike_Control(ros::NodeHandle *nh);
    void sensorsCallback(const my_project_msgs::Sensors &msg);
    void ackermannCallback(const ackermann_msgs::AckermannDriveStamped &msg);
    void initCallback(const std_msgs::String &msg);
    void timerEndCallback(const ros::TimerEvent &event);
    void odometryCalc();
    void sendAckerCommands(double linear_speed, double steering_angle);
    void saturate(double* input, double lowerLimit, double upperLimit);
    double calcDistance(double A, double B, double C, double x0, double y0);
    void controller(double motor_setpoint);
    double angulo_reta(double A, double B, double C, double x1, double y1);
};

CarLike_Control::CarLike_Control(ros::NodeHandle *nh)
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

    nh->getParam("/control_node/x_initial", initial_x_);
    nh->getParam("/control_node/y_initial", initial_y_);
    nh->getParam("/control_node/yaw_initial", initial_theta_);
    nh->getParam("/control_node/motor_setpoint", motor_setpoint);
    nh->getParam("/control_node/time", time);

    x_ = initial_x_;
    y_ = initial_y_;
    theta_ = initial_theta_;

    current_time_ = ros::Time::now();
    data_pub_ = nh->advertise<my_project_msgs::Data>("data_pub", 100);
    sub_sensors_ = nh->subscribe(topic_sub_, 100, &CarLike_Control::sensorsCallback, this);
    odom_pub_ = nh->advertise<nav_msgs::Odometry>("odom", 100);
    car_commands_ = nh->subscribe("/ackermann_cmd", 100, &CarLike_Control::ackermannCallback, this);
    car_commands_pub_ = nh->advertise<my_project_msgs::Command_ackermann>("/cmd_car", 100); 
    iniTeste = nh->subscribe("/iniTeste", 100, &CarLike_Control::initCallback, this);

}

void CarLike_Control::odometryCalc(){

    // Elapsed time
    current_time_ = ros::Time::now();
    double dt = 0.1;

    if(flag == 1){
    // Convert rpm to m/s
    vL_ = (2*M_PI*rpm_as5600_L_*wheelRadius_)/60;
    vR_ = (2*M_PI*rpm_as5600_R_*wheelRadius_)/60;

    // Longitudinal velocity
    current_speed = (vL_+vR_)/2;

    x_dot = current_speed * cos(theta_);
    y_dot = current_speed * sin(theta_);

    // Position estimation  
    x_ += x_dot*dt;
    y_ += y_dot*dt;

    // Orientation from Odom estimation
    if(steering_angle_ != 0){
        current_angular_velocity = current_speed * tan(steering_angle_) / wheelbase_;
        theta_odom_ += current_angular_velocity*dt;
    }

    // Maintain angle betwen [-3.14, 3.14]
    if(theta_odom_ > M_PI) {theta_odom_ -= 2*M_PI;}
    else if(theta_odom_ < -M_PI) {theta_odom_ += 2*M_PI;}
    
    // Car stopped condition
    if(abs(angularVelocityZ_) < 0.08) angularVelocityZ_ = 0;

    // Orientation from IMU
    theta_imu_ += angularVelocityZ_*dt;
    
    // Combined Orientation
    if(steering_angle_ != 0){
        theta_ = theta_imu_*0.8755 + theta_odom_*0.1245;
    }
    else{
        theta_ = theta_imu_;
    }
    theta_ += initial_theta_;

    // Maintain angle betwen [-3.14, 3.14]
    if(theta_ > M_PI) {theta_ -= 2*M_PI;}
    else if(theta_ < -M_PI) {theta_ += 2*M_PI;}    

    // Lateral controller function
    controller(motor_setpoint);
    }

    ROS_INFO("X: %.2f || Y: %.2f || Yaw: %.2f  || X_dot: %.2f || Y_dot: %.2f", x_, y_, theta_, x_dot, y_dot);

    // Create Quartenion from Yaw angle
    geometry_msgs::Quaternion odom_quat = tf::createQuaternionMsgFromYaw(theta_);

    // Publish transform over tf
    geometry_msgs::TransformStamped odom_tf;
    odom_tf.header.stamp = current_time_;
    odom_tf.header.frame_id = "odom";
    odom_tf.child_frame_id = "base_link";

    odom_tf.transform.translation.x = x_;
    odom_tf.transform.translation.y = y_;
    odom_tf.transform.translation.z = 0.0;
    odom_tf.transform.rotation = odom_quat;

    // Send transform
    odom_broadcaster_.sendTransform(odom_tf);

    // Make odom message
    nav_msgs::Odometry odom;
    odom.header.stamp = current_time_;
    odom.header.frame_id = "odom";

    // Set the position
    odom.pose.pose.position.x = x_;
    odom.pose.pose.position.y = y_;
    odom.pose.pose.position.z = 0.0;
    odom.pose.pose.orientation = odom_quat;

    // Set the velocity
    odom.child_frame_id = "base_link";
    odom.twist.twist.linear.x = x_dot;
    odom.twist.twist.linear.y = y_dot;
    odom.twist.twist.angular.z = angularVelocityZ_;

    // Publish the odometry message
    odom_pub_.publish(odom);

    // Publish message to get data
    // my_project_msgs::Data msg_data;
    // msg_data.Yaw_odom = theta_odom_;
    // msg_data.Yaw_mpu = theta_imu_;
    // msg_data.Yaw_combinado = theta_;
    // msg_data.dist = e;
    // msg_data.psi = psi;

    // data_pub_.publish(msg_data);
}

/**
 * Delimits the values betwen min and max
 * 
    @param input values to delimit
    @param lowerLimit minimum value
    @param upperLimit maximum value
*/
void CarLike_Control::saturate(double* input, double lowerLimit, double upperLimit){
  if(*input < lowerLimit) *input = lowerLimit;
  if(*input > upperLimit) *input = upperLimit;
}

/**
 * Distance's calculation for linear path like f(x) = mx or Ax + By + C = 0
 * 
 * @param A coefficient of the straight line equation
 * @param B coefficient of the straight line equation
 * @param C coefficient of the straight line equation
 * @param x0 robot's in x position
 * @param y0 robot's in y position
 *
*/
double CarLike_Control::calcDistance(double A, double B, double C, double x0, double y0){
    double distancia = abs(A * x0 + B * y0 + C) / sqrt(A*A + B*B);

    return distancia;
}

/**
 * Angle's calculation for linear path like f(x) = mx or Ax + By + C = 0
 * 
 * @param A coefficient of the straight line equation
 * @param B coefficient of the straight line equation
 * @param C coefficient of the straight line equation
 * @param x1 robot's in x position
 * @param y1 robot's in y position
*/
double CarLike_Control::angulo_reta(double A, double B, double C, double x1, double y1){

    double m = (-A/B);
    double c = (-C/B);

    double angulo = atan2(m, 1) - atan2(y1 - m*x1 - c, x1);

    return angulo;

}

/**
 * Lateral controller implementation
 * 
 * @param motor_setpoint PWM value to DC motor
*/
void CarLike_Control::controller(double motor_setpoint){

    double m = (-A/B);

    // States calculation
    e = calcDistance(A, B, C, x_, y_);
    psi = theta_ - angulo_reta(A, B, C, x_, y_);

    if(y_ < m*x_) e = (-1)*e;

    // Control signal
    double u = K_1*e + K_2*psi;
    saturate(&u, min_angle_servo_radians, max_angle_servo_radians);
    // ROS_INFO("u: %.2f", u);

    // Angle in degree for servo
    angle_servo = offset_angle_servo + (180/M_PI)*u;

    // Send r and u to ESP32
    sendAckerCommands(motor_setpoint, angle_servo);
}

void CarLike_Control::sendAckerCommands(double linear_speed, double steering_angle){
    my_project_msgs::Command_ackermann msg_cmd;
    msg_cmd.rpm = linear_speed;
    msg_cmd.servo_angle = steering_angle;

    car_commands_pub_.publish(msg_cmd);
}

void CarLike_Control::sensorsCallback(const my_project_msgs::Sensors &msg){

    this->rpm_eixo_ = msg.encoder_eixo;
    this->rpm_as5600_L_ = msg.encoder_as5600_L;
    this->rpm_as5600_R_ = msg.encoder_as5600_R;
    this->angularVelocityZ_ = msg.angularVelocity;

    // Odometry calculation
    odometryCalc();

    // ROS_INFO("Eixo:%.2f AS5600_L:%.2f AS5600_R:%.2f", this->rpm_eixo_, this->rpm_as5600_L_, this->rpm_as5600_R_);
}

void CarLike_Control::ackermannCallback(const ackermann_msgs::AckermannDriveStamped &msg){

    linear_speed_ = msg.drive.speed;
    steering_angle_ = msg.drive.steering_angle;

    // ROS_INFO("linear_vel:%.2f steering_angle:%.2f", linear_speed_, steering_angle_);

    // RPM setpoint
    rpm_ = (60/2*M_PI*0.0335)*(linear_speed_)*100;

    if(linear_speed_ > 0){
        saturate(&rpm_, 5, 240);
    }
    else if(linear_speed_< 0){
        saturate(&rpm_, -240, 5);
    }
    else if(linear_speed_ == 0){
        rpm_ = 0;
    }    
     
    angle_servo = offset_angle_servo + (180/M_PI)*steering_angle_;
    saturate(&angle_servo, 65, 119);

    sendAckerCommands(rpm_, angle_servo);

    // ROS_INFO("rpm:%.2f angle_servo:%.2f", rpm_, angle_servo);
}

void CarLike_Control::initCallback(const std_msgs::String &msg){
    if(msg.data == "start"){
        ros::NodeHandle nh;
        timerEnd = nh.createTimer(ros::Duration(time), &CarLike_Control::timerEndCallback, this);
        ROS_INFO("Teste iniciado");
        flag = 1;
    }  
}

void CarLike_Control::timerEndCallback(const ros::TimerEvent &event){
    if(flag == 1){
        ROS_INFO("Teste finalizado");
        sendAckerCommands(0.0, offset_angle_servo);
        flag = 2;
    }

}

int main(int argc,char **argv){
    ros::init(argc, argv, "control_node");
    ros::NodeHandle nh;

    CarLike_Control control = CarLike_Control(&nh);

    ros::spin();

    return 0;
}