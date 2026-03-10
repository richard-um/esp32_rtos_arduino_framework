#include "os.h"
#include <stdio.h>

namespace os
{

SemaphoreHandle_t log::mutex_ = nullptr;

void log::printf(const char *fmt, ...)
{
  if (fmt == nullptr) {
    return;
  }

  if (mutex_ == nullptr) {
    mutex_ = xSemaphoreCreateMutex();
  }

  if (mutex_ != nullptr) {
    xSemaphoreTake(mutex_, portMAX_DELAY);
  }

  char buf[192];

  va_list ap;
  va_start(ap, fmt);
  vsnprintf(buf, sizeof(buf), fmt, ap);
  va_end(ap);

  Serial.print(buf);

  if (mutex_ != nullptr) {
    xSemaphoreGive(mutex_);
  }
}

void log::println(const char *text)
{
  if (text == nullptr) {
    return;
  }

  printf("%s\n", text);
}

} // namespace os
