#include "os.h"

namespace os
{

void core::delay_ms(uint32_t ms)
{
  vTaskDelay(pdMS_TO_TICKS(ms));
}

void core::yield()
{
  taskYIELD();
}

bool task::create(
    TaskFunction_t fn,
    const char *name,
    uint32_t stack,
    void *arg,
    UBaseType_t prio,
    handle_t *out)
{
#if CONFIG_FREERTOS_NUMBER_OF_CORES == 1
  return xTaskCreate(fn, name, stack, arg, prio, out) == pdPASS;
#else
  return xTaskCreatePinnedToCore(fn, name, stack, arg, prio, out, tskNO_AFFINITY) == pdPASS;
#endif
}

void task::remove(handle_t handle)
{
  vTaskDelete(handle);
}

} // namespace os
