#!/usr/bin/env python
import rospy
import csv
from my_project_msgs.msg import Sensors, Command_ackermann, Data
from nav_msgs.msg import Odometry

class listener:

    def __init__(self):
        # dados dos encoders
        self.rpm_encoder_eixo = 0.0
        self.rpm_L = 0.0
        self.rpm_R = 0.0

        # dados da odometria
        self.x = 0.0
        self.y = 0.0
        self.orientationZ = 0.0
        self.vX = 0.0
        self.vY = 0.0
        self.wZ = 0.0

        # referencia para o motor do eixo
        self.setpoint_motor = 0.0

        # sinal de controle para o servo motor
        self.angle_servo = 0.0
        self.u = 0.0

        # Dados de Yaw, distancia e orientacao
        self.yaw_odom = 0.0
        self.yaw_mpu = 0.0
        self.yaw_comb = 0.0
        self.dist = 0.0 
        self.psi = 0.0

        self.timer = rospy.Timer(rospy.Duration(0.1), self.timerCallback)
        self.sensors_sub = rospy.Subscriber("/sensors_values", Sensors, self.callback_sensors)
        self.odom_sub = rospy.Subscriber("/odom", Odometry, self.callback_odom)
        self.cmd_sub = rospy.Subscriber("/cmd_car", Command_ackermann, self.callback_cmd)
        self.data_sub = rospy.Subscriber("data_pub", Data, self.callback_data)

    def callback_sensors(self, data):
        self.rpm_encoder_eixo = data.encoder_eixo
        self.rpm_R = data.encoder_as5600_R
        self.rpm_L = data.encoder_as5600_L

    def callback_cmd(self, data):
    #  RPM ajustado para o motor
       self.setpoint_motor = data.rpm

    #  angulo ajustado para o servo motor com orientação reta em 89°
       self.angle_servo = data.servo_angle
    #  sinal de controle em rad (-20, 20)
       self.u = 89 - self.angle_servo

    def callback_data(self, data):
        # Yaw obtido na odometria
        self.yaw_odom = data.Yaw_odom
        self.yaw_mpu = data.Yaw_mpu
        self.yaw_comb = data.Yaw_combinado
        self.dist = data.dist
        self.psi = data.psi

    def callback_odom(self, data):
        # posicao
        self.x = data.pose.pose.position.x
        self.y = data.pose.pose.position.y
        self.orientationZ = data.pose.pose.orientation.z
        self.orientationW = data.pose.pose.orientation.w

        # velocidades
        self.vX = data.twist.twist.linear.x
        self.vY = data.twist.twist.linear.y
        self.wZ = data.twist.twist.angular.z

        # rospy.loginfo("yaw = %f  wz= %f", self.orientationZ, self.wZ)

    def timerCallback(self, event):
        data = [self.rpm_encoder_eixo, self.rpm_L, self.rpm_R, self.x, self.y, self.orientationZ, self.vX, self.vY, self.wZ, 
                self.setpoint_motor, self.angle_servo, self.u, self.yaw_odom, self.yaw_mpu, self.yaw_comb, self.dist, self.psi]

        # Nome do arquivo CSV
        nome_arquivo = "./dados_10.csv"

        with open(nome_arquivo, 'a', newline='') as arquivo_csv:
            escritor_csv = csv.writer(arquivo_csv)
            escritor_csv.writerow(data)



if __name__ == '__main__':
    try:
        rospy.init_node("listener_node", anonymous=True)
        listener()
        
        rospy.spin()
    except rospy.ROSInterruptException:
        pass
