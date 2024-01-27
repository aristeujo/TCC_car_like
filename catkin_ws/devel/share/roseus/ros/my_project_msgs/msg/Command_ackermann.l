;; Auto-generated. Do not edit!


(when (boundp 'my_project_msgs::Command_ackermann)
  (if (not (find-package "MY_PROJECT_MSGS"))
    (make-package "MY_PROJECT_MSGS"))
  (shadow 'Command_ackermann (find-package "MY_PROJECT_MSGS")))
(unless (find-package "MY_PROJECT_MSGS::COMMAND_ACKERMANN")
  (make-package "MY_PROJECT_MSGS::COMMAND_ACKERMANN"))

(in-package "ROS")
;;//! \htmlinclude Command_ackermann.msg.html


(defclass my_project_msgs::Command_ackermann
  :super ros::object
  :slots (_rpm _servo_angle ))

(defmethod my_project_msgs::Command_ackermann
  (:init
   (&key
    ((:rpm __rpm) 0.0)
    ((:servo_angle __servo_angle) 0.0)
    )
   (send-super :init)
   (setq _rpm (float __rpm))
   (setq _servo_angle (float __servo_angle))
   self)
  (:rpm
   (&optional __rpm)
   (if __rpm (setq _rpm __rpm)) _rpm)
  (:servo_angle
   (&optional __servo_angle)
   (if __servo_angle (setq _servo_angle __servo_angle)) _servo_angle)
  (:serialization-length
   ()
   (+
    ;; float64 _rpm
    8
    ;; float64 _servo_angle
    8
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float64 _rpm
       (sys::poke _rpm (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _servo_angle
       (sys::poke _servo_angle (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float64 _rpm
     (setq _rpm (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _servo_angle
     (setq _servo_angle (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;;
   self)
  )

(setf (get my_project_msgs::Command_ackermann :md5sum-) "26bc2f4c90960827d45039181ffa5114")
(setf (get my_project_msgs::Command_ackermann :datatype-) "my_project_msgs/Command_ackermann")
(setf (get my_project_msgs::Command_ackermann :definition-)
      "float64 rpm
float64 servo_angle
")



(provide :my_project_msgs/Command_ackermann "26bc2f4c90960827d45039181ffa5114")


