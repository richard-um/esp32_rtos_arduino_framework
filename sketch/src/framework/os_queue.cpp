#include "os.h"

namespace os
{

queue::handle_t queue::create(uint32_t len, uint32_t item_size)
{
  return xQueueCreate(len, item_size);
}

bool queue::send(handle_t q, const void *item, uint32_t timeout_ms)
{
  if (q == nullptr || item == nullptr) {
    return false;
  }

  return xQueueSend(q, item, pdMS_TO_TICKS(timeout_ms)) == pdTRUE;
}

bool queue::recv(handle_t q, void *item, uint32_t timeout_ms)
{
  if (q == nullptr || item == nullptr) {
    return false;
  }

  return xQueueReceive(q, item, pdMS_TO_TICKS(timeout_ms)) == pdTRUE;
}

} // namespace os
