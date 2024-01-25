; Auto-generated. Do not edit!


(cl:in-package my_project_msgs-msg)


;//! \htmlinclude Sensors.msg.html

(cl:defclass <Sensors> (roslisp-msg-protocol:ros-message)
  ((encoder_eixo
    :reader encoder_eixo
    :initarg :encoder_eixo
    :type cl:float
    :initform 0.0)
   (encoder_as5600_R
    :reader encoder_as5600_R
    :initarg :encoder_as5600_R
    :type cl:float
    :initform 0.0)
   (encoder_as5600_L
    :reader encoder_as5600_L
    :initarg :encoder_as5600_L
    :type cl:float
    :initform 0.0)
   (Yaw
    :reader Yaw
    :initarg :Yaw
    :type cl:float
    :initform 0.0)
   (servo_angle
    :reader servo_angle
    :initarg :servo_angle
    :type cl:float
    :initform 0.0))
)

(cl:defclass Sensors (<Sensors>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Sensors>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Sensors)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name my_project_msgs-msg:<Sensors> is deprecated: use my_project_msgs-msg:Sensors instead.")))

(cl:ensure-generic-function 'encoder_eixo-val :lambda-list '(m))
(cl:defmethod encoder_eixo-val ((m <Sensors>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader my_project_msgs-msg:encoder_eixo-val is deprecated.  Use my_project_msgs-msg:encoder_eixo instead.")
  (encoder_eixo m))

(cl:ensure-generic-function 'encoder_as5600_R-val :lambda-list '(m))
(cl:defmethod encoder_as5600_R-val ((m <Sensors>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader my_project_msgs-msg:encoder_as5600_R-val is deprecated.  Use my_project_msgs-msg:encoder_as5600_R instead.")
  (encoder_as5600_R m))

(cl:ensure-generic-function 'encoder_as5600_L-val :lambda-list '(m))
(cl:defmethod encoder_as5600_L-val ((m <Sensors>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader my_project_msgs-msg:encoder_as5600_L-val is deprecated.  Use my_project_msgs-msg:encoder_as5600_L instead.")
  (encoder_as5600_L m))

(cl:ensure-generic-function 'Yaw-val :lambda-list '(m))
(cl:defmethod Yaw-val ((m <Sensors>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader my_project_msgs-msg:Yaw-val is deprecated.  Use my_project_msgs-msg:Yaw instead.")
  (Yaw m))

(cl:ensure-generic-function 'servo_angle-val :lambda-list '(m))
(cl:defmethod servo_angle-val ((m <Sensors>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader my_project_msgs-msg:servo_angle-val is deprecated.  Use my_project_msgs-msg:servo_angle instead.")
  (servo_angle m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Sensors>) ostream)
  "Serializes a message object of type '<Sensors>"
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'encoder_eixo))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'encoder_as5600_R))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'encoder_as5600_L))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'Yaw))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'servo_angle))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Sensors>) istream)
  "Deserializes a message object of type '<Sensors>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'encoder_eixo) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'encoder_as5600_R) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'encoder_as5600_L) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'Yaw) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'servo_angle) (roslisp-utils:decode-double-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Sensors>)))
  "Returns string type for a message object of type '<Sensors>"
  "my_project_msgs/Sensors")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Sensors)))
  "Returns string type for a message object of type 'Sensors"
  "my_project_msgs/Sensors")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Sensors>)))
  "Returns md5sum for a message object of type '<Sensors>"
  "52013037679213ea4ad08aa61ccef2b0")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Sensors)))
  "Returns md5sum for a message object of type 'Sensors"
  "52013037679213ea4ad08aa61ccef2b0")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Sensors>)))
  "Returns full string definition for message of type '<Sensors>"
  (cl:format cl:nil "float64 encoder_eixo~%float64 encoder_as5600_R~%float64 encoder_as5600_L~%float64 Yaw~%float64 servo_angle~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Sensors)))
  "Returns full string definition for message of type 'Sensors"
  (cl:format cl:nil "float64 encoder_eixo~%float64 encoder_as5600_R~%float64 encoder_as5600_L~%float64 Yaw~%float64 servo_angle~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Sensors>))
  (cl:+ 0
     8
     8
     8
     8
     8
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Sensors>))
  "Converts a ROS message object to a list"
  (cl:list 'Sensors
    (cl:cons ':encoder_eixo (encoder_eixo msg))
    (cl:cons ':encoder_as5600_R (encoder_as5600_R msg))
    (cl:cons ':encoder_as5600_L (encoder_as5600_L msg))
    (cl:cons ':Yaw (Yaw msg))
    (cl:cons ':servo_angle (servo_angle msg))
))
