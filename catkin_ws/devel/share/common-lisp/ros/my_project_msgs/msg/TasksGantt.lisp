; Auto-generated. Do not edit!


(cl:in-package my_project_msgs-msg)


;//! \htmlinclude TasksGantt.msg.html

(cl:defclass <TasksGantt> (roslisp-msg-protocol:ros-message)
  ((task_states
    :reader task_states
    :initarg :task_states
    :type (cl:vector my_project_msgs-msg:TaskState)
   :initform (cl:make-array 0 :element-type 'my_project_msgs-msg:TaskState :initial-element (cl:make-instance 'my_project_msgs-msg:TaskState)))
   (wcet_sensor_read
    :reader wcet_sensor_read
    :initarg :wcet_sensor_read
    :type cl:float
    :initform 0.0)
   (wcet_publish_ros
    :reader wcet_publish_ros
    :initarg :wcet_publish_ros
    :type cl:float
    :initform 0.0)
   (wcet_motor_control
    :reader wcet_motor_control
    :initarg :wcet_motor_control
    :type cl:float
    :initform 0.0)
   (wcet_send_gantt
    :reader wcet_send_gantt
    :initarg :wcet_send_gantt
    :type cl:float
    :initform 0.0))
)

(cl:defclass TasksGantt (<TasksGantt>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <TasksGantt>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'TasksGantt)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name my_project_msgs-msg:<TasksGantt> is deprecated: use my_project_msgs-msg:TasksGantt instead.")))

(cl:ensure-generic-function 'task_states-val :lambda-list '(m))
(cl:defmethod task_states-val ((m <TasksGantt>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader my_project_msgs-msg:task_states-val is deprecated.  Use my_project_msgs-msg:task_states instead.")
  (task_states m))

(cl:ensure-generic-function 'wcet_sensor_read-val :lambda-list '(m))
(cl:defmethod wcet_sensor_read-val ((m <TasksGantt>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader my_project_msgs-msg:wcet_sensor_read-val is deprecated.  Use my_project_msgs-msg:wcet_sensor_read instead.")
  (wcet_sensor_read m))

(cl:ensure-generic-function 'wcet_publish_ros-val :lambda-list '(m))
(cl:defmethod wcet_publish_ros-val ((m <TasksGantt>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader my_project_msgs-msg:wcet_publish_ros-val is deprecated.  Use my_project_msgs-msg:wcet_publish_ros instead.")
  (wcet_publish_ros m))

(cl:ensure-generic-function 'wcet_motor_control-val :lambda-list '(m))
(cl:defmethod wcet_motor_control-val ((m <TasksGantt>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader my_project_msgs-msg:wcet_motor_control-val is deprecated.  Use my_project_msgs-msg:wcet_motor_control instead.")
  (wcet_motor_control m))

(cl:ensure-generic-function 'wcet_send_gantt-val :lambda-list '(m))
(cl:defmethod wcet_send_gantt-val ((m <TasksGantt>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader my_project_msgs-msg:wcet_send_gantt-val is deprecated.  Use my_project_msgs-msg:wcet_send_gantt instead.")
  (wcet_send_gantt m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <TasksGantt>) ostream)
  "Serializes a message object of type '<TasksGantt>"
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'task_states))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'task_states))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'wcet_sensor_read))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'wcet_publish_ros))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'wcet_motor_control))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'wcet_send_gantt))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <TasksGantt>) istream)
  "Deserializes a message object of type '<TasksGantt>"
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'task_states) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'task_states)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'my_project_msgs-msg:TaskState))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'wcet_sensor_read) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'wcet_publish_ros) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'wcet_motor_control) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'wcet_send_gantt) (roslisp-utils:decode-single-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<TasksGantt>)))
  "Returns string type for a message object of type '<TasksGantt>"
  "my_project_msgs/TasksGantt")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'TasksGantt)))
  "Returns string type for a message object of type 'TasksGantt"
  "my_project_msgs/TasksGantt")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<TasksGantt>)))
  "Returns md5sum for a message object of type '<TasksGantt>"
  "5262c66c69965c8531fa37eba78e2a23")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'TasksGantt)))
  "Returns md5sum for a message object of type 'TasksGantt"
  "5262c66c69965c8531fa37eba78e2a23")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<TasksGantt>)))
  "Returns full string definition for message of type '<TasksGantt>"
  (cl:format cl:nil "my_project_msgs/TaskState[] task_states~%float32 wcet_sensor_read~%float32 wcet_publish_ros~%float32 wcet_motor_control~%float32 wcet_send_gantt~%================================================================================~%MSG: my_project_msgs/TaskState~%int32 task_index~%int32 state     ~%uint32 timestamp~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'TasksGantt)))
  "Returns full string definition for message of type 'TasksGantt"
  (cl:format cl:nil "my_project_msgs/TaskState[] task_states~%float32 wcet_sensor_read~%float32 wcet_publish_ros~%float32 wcet_motor_control~%float32 wcet_send_gantt~%================================================================================~%MSG: my_project_msgs/TaskState~%int32 task_index~%int32 state     ~%uint32 timestamp~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <TasksGantt>))
  (cl:+ 0
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'task_states) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
     4
     4
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <TasksGantt>))
  "Converts a ROS message object to a list"
  (cl:list 'TasksGantt
    (cl:cons ':task_states (task_states msg))
    (cl:cons ':wcet_sensor_read (wcet_sensor_read msg))
    (cl:cons ':wcet_publish_ros (wcet_publish_ros msg))
    (cl:cons ':wcet_motor_control (wcet_motor_control msg))
    (cl:cons ':wcet_send_gantt (wcet_send_gantt msg))
))
