#include "os.h"

namespace os
{

sem::handle_t sem::create(uint32_t max_count, uint32_t init_count)
{
  return xSemaphoreCreateCounting(max_count, init_count);
}

void sem::give(handle_t s)
{
  if (s != nullptr) {
    xSemaphoreGive(s);
  }
}

bool sem::take(handle_t s, uint32_t timeout_ms)
{
  if (s == nullptr) {
    return false;
  }

  return xSemaphoreTake(s, pdMS_TO_TICKS(timeout_ms)) == pdTRUE;
}

} // namespace os
