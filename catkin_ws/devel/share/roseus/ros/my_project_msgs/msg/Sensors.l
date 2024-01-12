;; Auto-generated. Do not edit!


(when (boundp 'my_project_msgs::Sensors)
  (if (not (find-package "MY_PROJECT_MSGS"))
    (make-package "MY_PROJECT_MSGS"))
  (shadow 'Sensors (find-package "MY_PROJECT_MSGS")))
(unless (find-package "MY_PROJECT_MSGS::SENSORS")
  (make-package "MY_PROJECT_MSGS::SENSORS"))

(in-package "ROS")
;;//! \htmlinclude Sensors.msg.html


(defclass my_project_msgs::Sensors
  :super ros::object
  :slots (_encoder_eixo _encoder_as5600_R _encoder_as5600_L ))

(defmethod my_project_msgs::Sensors
  (:init
   (&key
    ((:encoder_eixo __encoder_eixo) 0.0)
    ((:encoder_as5600_R __encoder_as5600_R) 0.0)
    ((:encoder_as5600_L __encoder_as5600_L) 0.0)
    )
   (send-super :init)
   (setq _encoder_eixo (float __encoder_eixo))
   (setq _encoder_as5600_R (float __encoder_as5600_R))
   (setq _encoder_as5600_L (float __encoder_as5600_L))
   self)
  (:encoder_eixo
   (&optional __encoder_eixo)
   (if __encoder_eixo (setq _encoder_eixo __encoder_eixo)) _encoder_eixo)
  (:encoder_as5600_R
   (&optional __encoder_as5600_R)
   (if __encoder_as5600_R (setq _encoder_as5600_R __encoder_as5600_R)) _encoder_as5600_R)
  (:encoder_as5600_L
   (&optional __encoder_as5600_L)
   (if __encoder_as5600_L (setq _encoder_as5600_L __encoder_as5600_L)) _encoder_as5600_L)
  (:serialization-length
   ()
   (+
    ;; float64 _encoder_eixo
    8
    ;; float64 _encoder_as5600_R
    8
    ;; float64 _encoder_as5600_L
    8
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float64 _encoder_eixo
       (sys::poke _encoder_eixo (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _encoder_as5600_R
       (sys::poke _encoder_as5600_R (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _encoder_as5600_L
       (sys::poke _encoder_as5600_L (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float64 _encoder_eixo
     (setq _encoder_eixo (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _encoder_as5600_R
     (setq _encoder_as5600_R (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _encoder_as5600_L
     (setq _encoder_as5600_L (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;;
   self)
  )

(setf (get my_project_msgs::Sensors :md5sum-) "4fb8452640ac8fb23177d835e52d73c4")
(setf (get my_project_msgs::Sensors :datatype-) "my_project_msgs/Sensors")
(setf (get my_project_msgs::Sensors :definition-)
      "float64 encoder_eixo
float64 encoder_as5600_R
float64 encoder_as5600_L
")



(provide :my_project_msgs/Sensors "4fb8452640ac8fb23177d835e52d73c4")


