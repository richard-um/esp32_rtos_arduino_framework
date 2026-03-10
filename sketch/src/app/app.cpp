#include "app.h"

void app::main()
{
  queue_ = queue::create(8, sizeof(message_t));
  lock_ = mutex::create();
  timer_ = timer::create("heartbeat", 2000, true, this, timer_heartbeat);

  log::println("[BOOT] app::main");

  if (queue_ == nullptr) {
    log::println("[FATAL] queue create failed");
    while (1) {
      core::delay_ms(1000);
    }
  }

  if (lock_ == nullptr) {
    log::println("[FATAL] mutex create failed");
    while (1) {
      core::delay_ms(1000);
    }
  }

  if (timer_ != nullptr) {
    timer::start(timer_);
  }

  if (!task::create(task_worker, "worker", 4096, this, 2, nullptr)) {
    log::println("[FATAL] task create failed");
    while (1) {
      core::delay_ms(1000);
    }
  }

  while (1) {
    message_t msg;

    if (queue::recv(queue_, &msg, 1000)) {
      mutex::lock(lock_);
      counter_ = msg.tick;
      mutex::unlock(lock_);

      log::printf("[APP] tick=%lu\n", (unsigned long)counter_);
    }
  }
}

void app::task_worker(void *arg)
{
  app *self = static_cast<app *>(arg);
  uint32_t tick = 0;

  while (1) {
    message_t msg;
    tick++;
    msg.tick = tick;

    queue::send(self->queue_, &msg, 10);
    core::delay_ms(1000);
  }
}

void app::timer_heartbeat(timer::handle_t timer)
{
  app *self = static_cast<app *>(timer::arg(timer));

  if (self == nullptr) {
    return;
  }

  log::printf("[TIMER] heartbeat counter=%lu\n", (unsigned long)self->counter_);
}
