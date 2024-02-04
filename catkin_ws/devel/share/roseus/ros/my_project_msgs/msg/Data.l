;; Auto-generated. Do not edit!


(when (boundp 'my_project_msgs::Data)
  (if (not (find-package "MY_PROJECT_MSGS"))
    (make-package "MY_PROJECT_MSGS"))
  (shadow 'Data (find-package "MY_PROJECT_MSGS")))
(unless (find-package "MY_PROJECT_MSGS::DATA")
  (make-package "MY_PROJECT_MSGS::DATA"))

(in-package "ROS")
;;//! \htmlinclude Data.msg.html


(defclass my_project_msgs::Data
  :super ros::object
  :slots (_Yaw_odom _Yaw_mpu _Yaw_combinado _dist _psi ))

(defmethod my_project_msgs::Data
  (:init
   (&key
    ((:Yaw_odom __Yaw_odom) 0.0)
    ((:Yaw_mpu __Yaw_mpu) 0.0)
    ((:Yaw_combinado __Yaw_combinado) 0.0)
    ((:dist __dist) 0.0)
    ((:psi __psi) 0.0)
    )
   (send-super :init)
   (setq _Yaw_odom (float __Yaw_odom))
   (setq _Yaw_mpu (float __Yaw_mpu))
   (setq _Yaw_combinado (float __Yaw_combinado))
   (setq _dist (float __dist))
   (setq _psi (float __psi))
   self)
  (:Yaw_odom
   (&optional __Yaw_odom)
   (if __Yaw_odom (setq _Yaw_odom __Yaw_odom)) _Yaw_odom)
  (:Yaw_mpu
   (&optional __Yaw_mpu)
   (if __Yaw_mpu (setq _Yaw_mpu __Yaw_mpu)) _Yaw_mpu)
  (:Yaw_combinado
   (&optional __Yaw_combinado)
   (if __Yaw_combinado (setq _Yaw_combinado __Yaw_combinado)) _Yaw_combinado)
  (:dist
   (&optional __dist)
   (if __dist (setq _dist __dist)) _dist)
  (:psi
   (&optional __psi)
   (if __psi (setq _psi __psi)) _psi)
  (:serialization-length
   ()
   (+
    ;; float64 _Yaw_odom
    8
    ;; float64 _Yaw_mpu
    8
    ;; float64 _Yaw_combinado
    8
    ;; float64 _dist
    8
    ;; float64 _psi
    8
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float64 _Yaw_odom
       (sys::poke _Yaw_odom (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _Yaw_mpu
       (sys::poke _Yaw_mpu (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _Yaw_combinado
       (sys::poke _Yaw_combinado (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _dist
       (sys::poke _dist (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _psi
       (sys::poke _psi (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float64 _Yaw_odom
     (setq _Yaw_odom (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _Yaw_mpu
     (setq _Yaw_mpu (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _Yaw_combinado
     (setq _Yaw_combinado (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _dist
     (setq _dist (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _psi
     (setq _psi (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;;
   self)
  )

(setf (get my_project_msgs::Data :md5sum-) "3376fc8753ba296918120944d2f95a14")
(setf (get my_project_msgs::Data :datatype-) "my_project_msgs/Data")
(setf (get my_project_msgs::Data :definition-)
      "float64 Yaw_odom
float64 Yaw_mpu
float64 Yaw_combinado
float64 dist
float64 psi
")



(provide :my_project_msgs/Data "3376fc8753ba296918120944d2f95a14")


