#include "../app/app.h"
#include "os.h"

extern "C" bool framework_entry(void)
{
  static app application;

  os::log::println("[BOOT] framework_entry");
  application.run();

  return true;
}
