# ESP32 RTOS Framework (Arduino)

Lightweight **application framework for ESP32** built on top of  
**Arduino Core + FreeRTOS**.

This project provides a minimal **RTOS abstraction layer** and a clean
**application structure** suitable for embedded firmware projects.

Designed for engineers who want **RTOS style firmware architecture**
while still using the **Arduino ecosystem**.

---

# Features

- FreeRTOS abstraction layer
- Task / Queue / Mutex / Semaphore wrapper
- Timer API
- Simple logging interface
- Clean separation of framework and application
- Arduino IDE compatible
- ESP32 / ESP32-C3 / ESP32-C6 compatible

---

# Architecture

```
Arduino Core
     │
FreeRTOS Kernel
     │
Framework Layer (os_*)
     │
Application Layer (app)
```

---

# Project Structure

```
sketch/
 ├─ src/
 │   ├─ framework/
 │   │   ├─ app_entry.cpp
 │   │   ├─ os_api.c
 │   │   └─ fwk_internal.h
 │   │
 │   └─ app/
 │       ├─ app.cpp
 │       └─ app.h
```

Framework layer provides **RTOS abstraction**.

Application layer contains **user firmware logic**.

---

# Execution Flow

```
Arduino setup()
      ↓
framework_entry()
      ↓
app()
```

The framework starts the application entry point.

---

# Application Entry

Application must implement:

```
bool app(void);
```

Example:

```cpp
#include "app.h"

bool app(void)
{
    while (true)
    {
        app_log("hello world\n");
        os_delay_ms(1000);
    }

    return true;
}
```

---

# OS Abstraction API

### Task

```
bool os_task_create(
    TaskFunction_t fn,
    const char *name,
    uint32_t stack,
    void *arg,
    UBaseType_t prio,
    os_task_t *out);
```

### Queue

```
os_queue_t os_queue_create(uint32_t len, uint32_t item_size);

bool os_queue_send(os_queue_t q, const void *item, uint32_t timeout_ms);
bool os_queue_recv(os_queue_t q, void *item, uint32_t timeout_ms);
```

### Mutex

```
os_mutex_t os_mutex_create();
bool os_mutex_lock(os_mutex_t m, uint32_t timeout_ms);
void os_mutex_unlock(os_mutex_t m);
```

### Semaphore

```
os_sem_t os_sem_create(uint32_t init_count);
bool os_sem_take(os_sem_t s, uint32_t timeout_ms);
void os_sem_give(os_sem_t s);
```

### Timer

```
os_timer_t os_timer_create(
    const char *name,
    uint32_t period_ms,
    bool repeat,
    void (*cb)(void *),
    void *arg);
```

---

# Logging

```
void app_log(const char *fmt, ...);
```

Example

```
app_log("temperature = %d\n", value);
```

---

# Utilities

```
void os_delay_ms(uint32_t ms);
void os_yield(void);
```

---

# Design Goals

- Clean firmware architecture
- RTOS style development on Arduino
- Minimal overhead
- Easy portability
- Maintain Arduino compatibility

---

# Roadmap

Planned features:

- BLE manager
- WiFi manager
- OTA update
- NVS configuration storage
- CLI shell
- advanced logging

---

# Supported Boards

- ESP32
- ESP32‑C3
- ESP32‑C6
- ESP32‑S3

---

# License

MIT License
