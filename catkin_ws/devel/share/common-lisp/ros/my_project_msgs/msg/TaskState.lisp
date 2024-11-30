; Auto-generated. Do not edit!


(cl:in-package my_project_msgs-msg)


;//! \htmlinclude TaskState.msg.html

(cl:defclass <TaskState> (roslisp-msg-protocol:ros-message)
  ((task_index
    :reader task_index
    :initarg :task_index
    :type cl:integer
    :initform 0)
   (state
    :reader state
    :initarg :state
    :type cl:integer
    :initform 0)
   (timestamp
    :reader timestamp
    :initarg :timestamp
    :type cl:integer
    :initform 0))
)

(cl:defclass TaskState (<TaskState>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <TaskState>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'TaskState)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name my_project_msgs-msg:<TaskState> is deprecated: use my_project_msgs-msg:TaskState instead.")))

(cl:ensure-generic-function 'task_index-val :lambda-list '(m))
(cl:defmethod task_index-val ((m <TaskState>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader my_project_msgs-msg:task_index-val is deprecated.  Use my_project_msgs-msg:task_index instead.")
  (task_index m))

(cl:ensure-generic-function 'state-val :lambda-list '(m))
(cl:defmethod state-val ((m <TaskState>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader my_project_msgs-msg:state-val is deprecated.  Use my_project_msgs-msg:state instead.")
  (state m))

(cl:ensure-generic-function 'timestamp-val :lambda-list '(m))
(cl:defmethod timestamp-val ((m <TaskState>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader my_project_msgs-msg:timestamp-val is deprecated.  Use my_project_msgs-msg:timestamp instead.")
  (timestamp m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <TaskState>) ostream)
  "Serializes a message object of type '<TaskState>"
  (cl:let* ((signed (cl:slot-value msg 'task_index)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'state)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'timestamp)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'timestamp)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'timestamp)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'timestamp)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <TaskState>) istream)
  "Deserializes a message object of type '<TaskState>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'task_index) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'state) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'timestamp)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'timestamp)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'timestamp)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'timestamp)) (cl:read-byte istream))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<TaskState>)))
  "Returns string type for a message object of type '<TaskState>"
  "my_project_msgs/TaskState")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'TaskState)))
  "Returns string type for a message object of type 'TaskState"
  "my_project_msgs/TaskState")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<TaskState>)))
  "Returns md5sum for a message object of type '<TaskState>"
  "c9b75f49a4033f347da6f7f095be60f2")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'TaskState)))
  "Returns md5sum for a message object of type 'TaskState"
  "c9b75f49a4033f347da6f7f095be60f2")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<TaskState>)))
  "Returns full string definition for message of type '<TaskState>"
  (cl:format cl:nil "int32 task_index~%int32 state     ~%uint32 timestamp~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'TaskState)))
  "Returns full string definition for message of type 'TaskState"
  (cl:format cl:nil "int32 task_index~%int32 state     ~%uint32 timestamp~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <TaskState>))
  (cl:+ 0
     4
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <TaskState>))
  "Converts a ROS message object to a list"
  (cl:list 'TaskState
    (cl:cons ':task_index (task_index msg))
    (cl:cons ':state (state msg))
    (cl:cons ':timestamp (timestamp msg))
))
