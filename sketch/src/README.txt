Arduino IDE sketch structure:

arduino_esp32_framework_rewrite/
├─ arduino_esp32_framework_rewrite.ino
└─ src/
   ├─ app_base.h / app_base.cpp
   ├─ app.h / app.cpp
   ├─ app_entry.cpp
   ├─ os.h
   ├─ os_core.cpp
   ├─ os_queue.cpp
   ├─ os_mutex.cpp
   ├─ os_sem.cpp
   ├─ os_timer.cpp
   ├─ os_event.cpp
   └─ os_log.cpp

Application rule:
- Start coding in src/app.cpp
- Put application logic in app::main()

Framework flow:
- setup() -> framework_entry() -> static app instance -> app.run() -> app::main()

Notes:
- Class-based application framework.
- Class-based os wrapper via namespace os.
- Single-core ESP32-C6 safe task creation path included.
