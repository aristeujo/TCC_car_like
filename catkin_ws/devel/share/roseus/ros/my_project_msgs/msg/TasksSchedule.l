;; Auto-generated. Do not edit!


(when (boundp 'my_project_msgs::TasksSchedule)
  (if (not (find-package "MY_PROJECT_MSGS"))
    (make-package "MY_PROJECT_MSGS"))
  (shadow 'TasksSchedule (find-package "MY_PROJECT_MSGS")))
(unless (find-package "MY_PROJECT_MSGS::TASKSSCHEDULE")
  (make-package "MY_PROJECT_MSGS::TASKSSCHEDULE"))

(in-package "ROS")
;;//! \htmlinclude TasksSchedule.msg.html


(defclass my_project_msgs::TasksSchedule
  :super ros::object
  :slots (_task_sensor _task_motor_control _task_publish _task_scheduler ))

(defmethod my_project_msgs::TasksSchedule
  (:init
   (&key
    ((:task_sensor __task_sensor) "")
    ((:task_motor_control __task_motor_control) "")
    ((:task_publish __task_publish) "")
    ((:task_scheduler __task_scheduler) "")
    )
   (send-super :init)
   (setq _task_sensor (string __task_sensor))
   (setq _task_motor_control (string __task_motor_control))
   (setq _task_publish (string __task_publish))
   (setq _task_scheduler (string __task_scheduler))
   self)
  (:task_sensor
   (&optional __task_sensor)
   (if __task_sensor (setq _task_sensor __task_sensor)) _task_sensor)
  (:task_motor_control
   (&optional __task_motor_control)
   (if __task_motor_control (setq _task_motor_control __task_motor_control)) _task_motor_control)
  (:task_publish
   (&optional __task_publish)
   (if __task_publish (setq _task_publish __task_publish)) _task_publish)
  (:task_scheduler
   (&optional __task_scheduler)
   (if __task_scheduler (setq _task_scheduler __task_scheduler)) _task_scheduler)
  (:serialization-length
   ()
   (+
    ;; string _task_sensor
    4 (length _task_sensor)
    ;; string _task_motor_control
    4 (length _task_motor_control)
    ;; string _task_publish
    4 (length _task_publish)
    ;; string _task_scheduler
    4 (length _task_scheduler)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; string _task_sensor
       (write-long (length _task_sensor) s) (princ _task_sensor s)
     ;; string _task_motor_control
       (write-long (length _task_motor_control) s) (princ _task_motor_control s)
     ;; string _task_publish
       (write-long (length _task_publish) s) (princ _task_publish s)
     ;; string _task_scheduler
       (write-long (length _task_scheduler) s) (princ _task_scheduler s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; string _task_sensor
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _task_sensor (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; string _task_motor_control
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _task_motor_control (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; string _task_publish
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _task_publish (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; string _task_scheduler
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _task_scheduler (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;;
   self)
  )

(setf (get my_project_msgs::TasksSchedule :md5sum-) "1f7390576d604b72feca1119d3cd344a")
(setf (get my_project_msgs::TasksSchedule :datatype-) "my_project_msgs/TasksSchedule")
(setf (get my_project_msgs::TasksSchedule :definition-)
      "string task_sensor
string task_motor_control
string task_publish
string task_scheduler

")



(provide :my_project_msgs/TasksSchedule "1f7390576d604b72feca1119d3cd344a")


