#pragma once

#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/queue.h>
#include <freertos/semphr.h>
#include <freertos/event_groups.h>
#include <freertos/timers.h>
#include <stdarg.h>

namespace os
{

class core
{
public:
  static void delay_ms(uint32_t ms);
  static void yield();
};

class task
{
public:
  using handle_t = TaskHandle_t;

  static bool create(
      TaskFunction_t fn,
      const char *name,
      uint32_t stack,
      void *arg,
      UBaseType_t prio,
      handle_t *out);

  static void remove(handle_t handle = nullptr);
};

class queue
{
public:
  using handle_t = QueueHandle_t;

  static handle_t create(uint32_t len, uint32_t item_size);
  static bool send(handle_t q, const void *item, uint32_t timeout_ms);
  static bool recv(handle_t q, void *item, uint32_t timeout_ms);
};

class mutex
{
public:
  using handle_t = SemaphoreHandle_t;

  static handle_t create();
  static bool lock(handle_t m, uint32_t timeout_ms = portMAX_DELAY);
  static void unlock(handle_t m);
};

class sem
{
public:
  using handle_t = SemaphoreHandle_t;

  static handle_t create(uint32_t max_count, uint32_t init_count);
  static void give(handle_t s);
  static bool take(handle_t s, uint32_t timeout_ms);
};

class timer
{
public:
  using handle_t = TimerHandle_t;
  using callback_t = void (*)(handle_t timer);

  static handle_t create(
      const char *name,
      uint32_t period_ms,
      bool repeat,
      void *arg,
      callback_t cb);

  static bool start(handle_t t, uint32_t timeout_ms = 0);
  static void *arg(handle_t t);

private:
  static void trampoline(TimerHandle_t handle);
};

class event
{
public:
  using handle_t = EventGroupHandle_t;

  static handle_t create();
  static uint32_t set(handle_t e, uint32_t bits);
  static uint32_t wait(
      handle_t e,
      uint32_t bits,
      bool clear_on_exit,
      bool wait_all,
      uint32_t timeout_ms);
};

class log
{
public:
  static void printf(const char *fmt, ...);
  static void println(const char *text);

private:
  static SemaphoreHandle_t mutex_;
};

} // namespace os
