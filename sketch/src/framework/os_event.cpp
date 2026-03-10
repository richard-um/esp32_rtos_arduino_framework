#include "os.h"

namespace os
{

event::handle_t event::create()
{
  return xEventGroupCreate();
}

uint32_t event::set(handle_t e, uint32_t bits)
{
  if (e == nullptr) {
    return 0;
  }

  return xEventGroupSetBits(e, bits);
}

uint32_t event::wait(
    handle_t e,
    uint32_t bits,
    bool clear_on_exit,
    bool wait_all,
    uint32_t timeout_ms)
{
  if (e == nullptr) {
    return 0;
  }

  return xEventGroupWaitBits(
      e,
      bits,
      clear_on_exit ? pdTRUE : pdFALSE,
      wait_all ? pdTRUE : pdFALSE,
      pdMS_TO_TICKS(timeout_ms));
}

} // namespace os
