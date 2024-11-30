; Auto-generated. Do not edit!


(cl:in-package my_project_msgs-msg)


;//! \htmlinclude TasksSchedule.msg.html

(cl:defclass <TasksSchedule> (roslisp-msg-protocol:ros-message)
  ((task_sensor
    :reader task_sensor
    :initarg :task_sensor
    :type cl:string
    :initform "")
   (task_motor_control
    :reader task_motor_control
    :initarg :task_motor_control
    :type cl:string
    :initform "")
   (task_publish
    :reader task_publish
    :initarg :task_publish
    :type cl:string
    :initform "")
   (task_scheduler
    :reader task_scheduler
    :initarg :task_scheduler
    :type cl:string
    :initform ""))
)

(cl:defclass TasksSchedule (<TasksSchedule>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <TasksSchedule>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'TasksSchedule)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name my_project_msgs-msg:<TasksSchedule> is deprecated: use my_project_msgs-msg:TasksSchedule instead.")))

(cl:ensure-generic-function 'task_sensor-val :lambda-list '(m))
(cl:defmethod task_sensor-val ((m <TasksSchedule>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader my_project_msgs-msg:task_sensor-val is deprecated.  Use my_project_msgs-msg:task_sensor instead.")
  (task_sensor m))

(cl:ensure-generic-function 'task_motor_control-val :lambda-list '(m))
(cl:defmethod task_motor_control-val ((m <TasksSchedule>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader my_project_msgs-msg:task_motor_control-val is deprecated.  Use my_project_msgs-msg:task_motor_control instead.")
  (task_motor_control m))

(cl:ensure-generic-function 'task_publish-val :lambda-list '(m))
(cl:defmethod task_publish-val ((m <TasksSchedule>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader my_project_msgs-msg:task_publish-val is deprecated.  Use my_project_msgs-msg:task_publish instead.")
  (task_publish m))

(cl:ensure-generic-function 'task_scheduler-val :lambda-list '(m))
(cl:defmethod task_scheduler-val ((m <TasksSchedule>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader my_project_msgs-msg:task_scheduler-val is deprecated.  Use my_project_msgs-msg:task_scheduler instead.")
  (task_scheduler m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <TasksSchedule>) ostream)
  "Serializes a message object of type '<TasksSchedule>"
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'task_sensor))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'task_sensor))
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'task_motor_control))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'task_motor_control))
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'task_publish))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'task_publish))
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'task_scheduler))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'task_scheduler))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <TasksSchedule>) istream)
  "Deserializes a message object of type '<TasksSchedule>"
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'task_sensor) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'task_sensor) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'task_motor_control) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'task_motor_control) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'task_publish) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'task_publish) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'task_scheduler) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'task_scheduler) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<TasksSchedule>)))
  "Returns string type for a message object of type '<TasksSchedule>"
  "my_project_msgs/TasksSchedule")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'TasksSchedule)))
  "Returns string type for a message object of type 'TasksSchedule"
  "my_project_msgs/TasksSchedule")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<TasksSchedule>)))
  "Returns md5sum for a message object of type '<TasksSchedule>"
  "1f7390576d604b72feca1119d3cd344a")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'TasksSchedule)))
  "Returns md5sum for a message object of type 'TasksSchedule"
  "1f7390576d604b72feca1119d3cd344a")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<TasksSchedule>)))
  "Returns full string definition for message of type '<TasksSchedule>"
  (cl:format cl:nil "string task_sensor~%string task_motor_control~%string task_publish~%string task_scheduler~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'TasksSchedule)))
  "Returns full string definition for message of type 'TasksSchedule"
  (cl:format cl:nil "string task_sensor~%string task_motor_control~%string task_publish~%string task_scheduler~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <TasksSchedule>))
  (cl:+ 0
     4 (cl:length (cl:slot-value msg 'task_sensor))
     4 (cl:length (cl:slot-value msg 'task_motor_control))
     4 (cl:length (cl:slot-value msg 'task_publish))
     4 (cl:length (cl:slot-value msg 'task_scheduler))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <TasksSchedule>))
  "Converts a ROS message object to a list"
  (cl:list 'TasksSchedule
    (cl:cons ':task_sensor (task_sensor msg))
    (cl:cons ':task_motor_control (task_motor_control msg))
    (cl:cons ':task_publish (task_publish msg))
    (cl:cons ':task_scheduler (task_scheduler msg))
))
