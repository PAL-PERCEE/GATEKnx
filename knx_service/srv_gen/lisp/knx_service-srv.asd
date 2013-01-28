
(cl:in-package :asdf)

(defsystem "knx_service-srv"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "KnxSet" :depends-on ("_package_KnxSet"))
    (:file "_package_KnxSet" :depends-on ("_package"))
  ))