#pragma once

#include <Arduino.h>

#include "../framework/app_base.h"
#include "../framework/os.h"

using namespace os;

class app : public app_base
{
protected:
  void main() override;

private:
  struct message_t {
    uint32_t tick;
  };

  static void task_worker(void *arg);
  static void timer_heartbeat(timer::handle_t timer);

private:
  uint32_t counter_ = 0;
  queue::handle_t queue_ = nullptr;
  mutex::handle_t lock_ = nullptr;
  timer::handle_t timer_ = nullptr;
};
