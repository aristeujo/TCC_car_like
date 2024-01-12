
(cl:in-package :asdf)

(defsystem "my_project_msgs-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "Sensors" :depends-on ("_package_Sensors"))
    (:file "_package_Sensors" :depends-on ("_package"))
  ))