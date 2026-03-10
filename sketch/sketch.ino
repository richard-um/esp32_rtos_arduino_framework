#include <Arduino.h>

extern "C" bool framework_entry(void);

void setup()
{
  Serial.begin(115200);
  delay(300);

  if (!framework_entry()) {
    Serial.println("[FATAL] framework_entry failed");
    while (1) {
      delay(1000);
    }
  }
}

void loop()
{
  vTaskDelay(pdMS_TO_TICKS(1000));
}
