;; Auto-generated. Do not edit!


(when (boundp 'my_project_msgs::TasksGantt)
  (if (not (find-package "MY_PROJECT_MSGS"))
    (make-package "MY_PROJECT_MSGS"))
  (shadow 'TasksGantt (find-package "MY_PROJECT_MSGS")))
(unless (find-package "MY_PROJECT_MSGS::TASKSGANTT")
  (make-package "MY_PROJECT_MSGS::TASKSGANTT"))

(in-package "ROS")
;;//! \htmlinclude TasksGantt.msg.html


(defclass my_project_msgs::TasksGantt
  :super ros::object
  :slots (_task_states _wcet_sensor_read _wcet_publish_ros _wcet_motor_control _wcet_send_gantt ))

(defmethod my_project_msgs::TasksGantt
  (:init
   (&key
    ((:task_states __task_states) ())
    ((:wcet_sensor_read __wcet_sensor_read) 0.0)
    ((:wcet_publish_ros __wcet_publish_ros) 0.0)
    ((:wcet_motor_control __wcet_motor_control) 0.0)
    ((:wcet_send_gantt __wcet_send_gantt) 0.0)
    )
   (send-super :init)
   (setq _task_states __task_states)
   (setq _wcet_sensor_read (float __wcet_sensor_read))
   (setq _wcet_publish_ros (float __wcet_publish_ros))
   (setq _wcet_motor_control (float __wcet_motor_control))
   (setq _wcet_send_gantt (float __wcet_send_gantt))
   self)
  (:task_states
   (&rest __task_states)
   (if (keywordp (car __task_states))
       (send* _task_states __task_states)
     (progn
       (if __task_states (setq _task_states (car __task_states)))
       _task_states)))
  (:wcet_sensor_read
   (&optional __wcet_sensor_read)
   (if __wcet_sensor_read (setq _wcet_sensor_read __wcet_sensor_read)) _wcet_sensor_read)
  (:wcet_publish_ros
   (&optional __wcet_publish_ros)
   (if __wcet_publish_ros (setq _wcet_publish_ros __wcet_publish_ros)) _wcet_publish_ros)
  (:wcet_motor_control
   (&optional __wcet_motor_control)
   (if __wcet_motor_control (setq _wcet_motor_control __wcet_motor_control)) _wcet_motor_control)
  (:wcet_send_gantt
   (&optional __wcet_send_gantt)
   (if __wcet_send_gantt (setq _wcet_send_gantt __wcet_send_gantt)) _wcet_send_gantt)
  (:serialization-length
   ()
   (+
    ;; my_project_msgs/TaskState[] _task_states
    (apply #'+ (send-all _task_states :serialization-length)) 4
    ;; float32 _wcet_sensor_read
    4
    ;; float32 _wcet_publish_ros
    4
    ;; float32 _wcet_motor_control
    4
    ;; float32 _wcet_send_gantt
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; my_project_msgs/TaskState[] _task_states
     (write-long (length _task_states) s)
     (dolist (elem _task_states)
       (send elem :serialize s)
       )
     ;; float32 _wcet_sensor_read
       (sys::poke _wcet_sensor_read (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _wcet_publish_ros
       (sys::poke _wcet_publish_ros (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _wcet_motor_control
       (sys::poke _wcet_motor_control (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _wcet_send_gantt
       (sys::poke _wcet_send_gantt (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; my_project_msgs/TaskState[] _task_states
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _task_states (let (r) (dotimes (i n) (push (instance my_project_msgs::TaskState :init) r)) r))
     (dolist (elem- _task_states)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;; float32 _wcet_sensor_read
     (setq _wcet_sensor_read (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _wcet_publish_ros
     (setq _wcet_publish_ros (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _wcet_motor_control
     (setq _wcet_motor_control (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _wcet_send_gantt
     (setq _wcet_send_gantt (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get my_project_msgs::TasksGantt :md5sum-) "5262c66c69965c8531fa37eba78e2a23")
(setf (get my_project_msgs::TasksGantt :datatype-) "my_project_msgs/TasksGantt")
(setf (get my_project_msgs::TasksGantt :definition-)
      "my_project_msgs/TaskState[] task_states
float32 wcet_sensor_read
float32 wcet_publish_ros
float32 wcet_motor_control
float32 wcet_send_gantt
================================================================================
MSG: my_project_msgs/TaskState
int32 task_index
int32 state     
uint32 timestamp


")



(provide :my_project_msgs/TasksGantt "5262c66c69965c8531fa37eba78e2a23")


