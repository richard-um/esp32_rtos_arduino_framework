# ESP32 RTOS Application Framework (Arduino)

![ESP32](https://img.shields.io/badge/ESP32-supported-blue)
![Arduino](https://img.shields.io/badge/Arduino-compatible-green)
![FreeRTOS](https://img.shields.io/badge/RTOS-FreeRTOS-orange)
![License](https://img.shields.io/badge/license-MIT-lightgrey)

A lightweight **C++ application framework for ESP32** built on top of  
**Arduino Core + FreeRTOS**.

This framework allows developers to write firmware using a **clean RTOS-style architecture**
while remaining fully compatible with the **Arduino build environment**.

Instead of placing all logic inside `setup()` and `loop()`, the framework introduces
a **structured application model using C++ classes and RTOS primitives**.

---

# Key Features

• Arduino IDE compatible  
• Built on ESP32 FreeRTOS kernel  
• Clean C++ application architecture  
• RTOS abstraction layer  
• Logging support  
• Modular OS wrapper APIs  

Supported primitives:

- Task
- Queue
- Mutex
- Semaphore
- Timer
- Event groups
- Logging

---

# Architecture

```
            +-------------------+
            |   Arduino Core    |
            +-------------------+
                     |
                     v
            +-------------------+
            |    FreeRTOS       |
            +-------------------+
                     |
                     v
            +-------------------+
            | Framework Layer   |
            |   (os namespace)  |
            +-------------------+
                     |
                     v
            +-------------------+
            | Application Layer |
            |   (app class)     |
            +-------------------+
```

---

# Execution Flow

```
Arduino Runtime
      |
      v
framework_entry()
      |
      v
app::run()
      |
      v
app::main()
```

Example entry implementation:

```cpp
extern "C" bool framework_entry(void)
{
    static app application;

    os::log::println("[BOOT] framework_entry");
    application.run();

    return true;
}
```

---

# Project Structure

```
sketch/
 ├─ src/
 │   ├─ framework/
 │   │   ├─ app_entry.cpp
 │   │   ├─ app_base.h
 │   │   ├─ app_base.cpp
 │   │   ├─ os.h
 │   │   ├─ os_core.cpp
 │   │   ├─ os_queue.cpp
 │   │   ├─ os_mutex.cpp
 │   │   ├─ os_sem.cpp
 │   │   ├─ os_timer.cpp
 │   │   ├─ os_event.cpp
 │   │   └─ os_log.cpp
 │   │
 │   └─ app/
 │       ├─ app.h
 │       └─ app.cpp
```

Framework implements RTOS abstractions.  
Application directory contains user firmware.

---

# Application Model

Applications inherit from `app_base`.

Example:

```cpp
class app : public app_base
{
protected:
    void main() override;
};
```

The framework runtime calls `run()` which invokes `main()`.

---

# Example Application

```cpp
void app::main()
{
    os::log::println("Application started");

    while (true)
    {
        os::log::println("tick");
        os::delay_ms(1000);
    }
}
```

---

# RTOS API (os namespace)

The framework wraps FreeRTOS primitives through the `os` namespace.

Modules include:

```
os::queue
os::mutex
os::sem
os::timer
os::event
os::log
```

Example queue:

```cpp
auto q = os::queue::create(10, sizeof(message_t));
```

Example mutex:

```cpp
auto m = os::mutex::create();
```

Example timer:

```cpp
auto t = os::timer::create("heartbeat", 1000, true, callback);
```

---

# Logging

```cpp
os::log::println("System ready");
```

---

# Why not use Arduino directly?

Traditional Arduino sketches:

```
setup()
loop()
```

This becomes difficult to scale for complex firmware.

The framework introduces:

• Structured application entry  
• RTOS primitives  
• Modular architecture  
• Maintainable firmware design

---

# Getting Started

1. Install ESP32 Arduino Core
2. Open project in Arduino IDE
3. Compile and upload to ESP32 board

Your application logic goes inside:

```
src/app/app.cpp
```

---

# Supported Boards

- ESP32
- ESP32-C3
- ESP32-C6
- ESP32-S3

---

# Roadmap

Planned modules:

- BLE manager
- WiFi manager
- OTA firmware update
- NVS configuration storage
- CLI shell
- Advanced logging

---

# License

MIT License
