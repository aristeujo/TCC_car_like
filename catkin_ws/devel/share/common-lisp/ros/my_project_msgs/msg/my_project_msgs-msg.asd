
(cl:in-package :asdf)

(defsystem "my_project_msgs-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "Command_ackermann" :depends-on ("_package_Command_ackermann"))
    (:file "_package_Command_ackermann" :depends-on ("_package"))
    (:file "Data" :depends-on ("_package_Data"))
    (:file "_package_Data" :depends-on ("_package"))
    (:file "Sensors" :depends-on ("_package_Sensors"))
    (:file "_package_Sensors" :depends-on ("_package"))
  ))