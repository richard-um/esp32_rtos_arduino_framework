#include "os.h"

namespace os
{

mutex::handle_t mutex::create()
{
  return xSemaphoreCreateMutex();
}

bool mutex::lock(handle_t m, uint32_t timeout_ms)
{
  if (m == nullptr) {
    return false;
  }

  TickType_t ticks = (timeout_ms == portMAX_DELAY)
    ? portMAX_DELAY
    : pdMS_TO_TICKS(timeout_ms);

  return xSemaphoreTake(m, ticks) == pdTRUE;
}

void mutex::unlock(handle_t m)
{
  if (m != nullptr) {
    xSemaphoreGive(m);
  }
}

} // namespace os
