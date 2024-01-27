; Auto-generated. Do not edit!


(cl:in-package my_project_msgs-msg)


;//! \htmlinclude Command_ackermann.msg.html

(cl:defclass <Command_ackermann> (roslisp-msg-protocol:ros-message)
  ((rpm
    :reader rpm
    :initarg :rpm
    :type cl:float
    :initform 0.0)
   (servo_angle
    :reader servo_angle
    :initarg :servo_angle
    :type cl:float
    :initform 0.0))
)

(cl:defclass Command_ackermann (<Command_ackermann>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Command_ackermann>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Command_ackermann)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name my_project_msgs-msg:<Command_ackermann> is deprecated: use my_project_msgs-msg:Command_ackermann instead.")))

(cl:ensure-generic-function 'rpm-val :lambda-list '(m))
(cl:defmethod rpm-val ((m <Command_ackermann>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader my_project_msgs-msg:rpm-val is deprecated.  Use my_project_msgs-msg:rpm instead.")
  (rpm m))

(cl:ensure-generic-function 'servo_angle-val :lambda-list '(m))
(cl:defmethod servo_angle-val ((m <Command_ackermann>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader my_project_msgs-msg:servo_angle-val is deprecated.  Use my_project_msgs-msg:servo_angle instead.")
  (servo_angle m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Command_ackermann>) ostream)
  "Serializes a message object of type '<Command_ackermann>"
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'rpm))))
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
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Command_ackermann>) istream)
  "Deserializes a message object of type '<Command_ackermann>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'rpm) (roslisp-utils:decode-double-float-bits bits)))
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
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Command_ackermann>)))
  "Returns string type for a message object of type '<Command_ackermann>"
  "my_project_msgs/Command_ackermann")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Command_ackermann)))
  "Returns string type for a message object of type 'Command_ackermann"
  "my_project_msgs/Command_ackermann")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Command_ackermann>)))
  "Returns md5sum for a message object of type '<Command_ackermann>"
  "26bc2f4c90960827d45039181ffa5114")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Command_ackermann)))
  "Returns md5sum for a message object of type 'Command_ackermann"
  "26bc2f4c90960827d45039181ffa5114")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Command_ackermann>)))
  "Returns full string definition for message of type '<Command_ackermann>"
  (cl:format cl:nil "float64 rpm~%float64 servo_angle~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Command_ackermann)))
  "Returns full string definition for message of type 'Command_ackermann"
  (cl:format cl:nil "float64 rpm~%float64 servo_angle~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Command_ackermann>))
  (cl:+ 0
     8
     8
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Command_ackermann>))
  "Converts a ROS message object to a list"
  (cl:list 'Command_ackermann
    (cl:cons ':rpm (rpm msg))
    (cl:cons ':servo_angle (servo_angle msg))
))
