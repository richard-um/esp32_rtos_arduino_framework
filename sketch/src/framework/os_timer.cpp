#include "os.h"
#include <stdlib.h>

namespace os
{

namespace
{
struct timer_ctx_t {
  timer::callback_t cb;
  void *arg;
};
}

timer::handle_t timer::create(
    const char *name,
    uint32_t period_ms,
    bool repeat,
    void *arg,
    callback_t cb)
{
  timer_ctx_t *ctx = static_cast<timer_ctx_t *>(malloc(sizeof(timer_ctx_t)));
  if (ctx == nullptr) {
    return nullptr;
  }

  ctx->cb = cb;
  ctx->arg = arg;

  handle_t t = xTimerCreate(
      name,
      pdMS_TO_TICKS(period_ms),
      repeat ? pdTRUE : pdFALSE,
      ctx,
      trampoline);

  if (t == nullptr) {
    free(ctx);
    return nullptr;
  }

  return t;
}

bool timer::start(handle_t t, uint32_t timeout_ms)
{
  if (t == nullptr) {
    return false;
  }

  return xTimerStart(t, pdMS_TO_TICKS(timeout_ms)) == pdPASS;
}

void *timer::arg(handle_t t)
{
  if (t == nullptr) {
    return nullptr;
  }

  timer_ctx_t *ctx = static_cast<timer_ctx_t *>(pvTimerGetTimerID(t));
  if (ctx == nullptr) {
    return nullptr;
  }

  return ctx->arg;
}

void timer::trampoline(TimerHandle_t handle)
{
  if (handle == nullptr) {
    return;
  }

  timer_ctx_t *ctx = static_cast<timer_ctx_t *>(pvTimerGetTimerID(handle));
  if (ctx != nullptr && ctx->cb != nullptr) {
    ctx->cb(handle);
  }
}

} // namespace os
