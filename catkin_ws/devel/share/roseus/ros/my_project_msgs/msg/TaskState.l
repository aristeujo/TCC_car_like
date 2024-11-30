;; Auto-generated. Do not edit!


(when (boundp 'my_project_msgs::TaskState)
  (if (not (find-package "MY_PROJECT_MSGS"))
    (make-package "MY_PROJECT_MSGS"))
  (shadow 'TaskState (find-package "MY_PROJECT_MSGS")))
(unless (find-package "MY_PROJECT_MSGS::TASKSTATE")
  (make-package "MY_PROJECT_MSGS::TASKSTATE"))

(in-package "ROS")
;;//! \htmlinclude TaskState.msg.html


(defclass my_project_msgs::TaskState
  :super ros::object
  :slots (_task_index _state _timestamp ))

(defmethod my_project_msgs::TaskState
  (:init
   (&key
    ((:task_index __task_index) 0)
    ((:state __state) 0)
    ((:timestamp __timestamp) 0)
    )
   (send-super :init)
   (setq _task_index (round __task_index))
   (setq _state (round __state))
   (setq _timestamp (round __timestamp))
   self)
  (:task_index
   (&optional __task_index)
   (if __task_index (setq _task_index __task_index)) _task_index)
  (:state
   (&optional __state)
   (if __state (setq _state __state)) _state)
  (:timestamp
   (&optional __timestamp)
   (if __timestamp (setq _timestamp __timestamp)) _timestamp)
  (:serialization-length
   ()
   (+
    ;; int32 _task_index
    4
    ;; int32 _state
    4
    ;; uint32 _timestamp
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int32 _task_index
       (write-long _task_index s)
     ;; int32 _state
       (write-long _state s)
     ;; uint32 _timestamp
       (write-long _timestamp s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int32 _task_index
     (setq _task_index (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _state
     (setq _state (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; uint32 _timestamp
     (setq _timestamp (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get my_project_msgs::TaskState :md5sum-) "c9b75f49a4033f347da6f7f095be60f2")
(setf (get my_project_msgs::TaskState :datatype-) "my_project_msgs/TaskState")
(setf (get my_project_msgs::TaskState :definition-)
      "int32 task_index
int32 state     
uint32 timestamp


")



(provide :my_project_msgs/TaskState "c9b75f49a4033f347da6f7f095be60f2")


