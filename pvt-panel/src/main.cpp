#include <Arduino.h>
#include <TFT_eSPI.h>
#include <XPT2046_Touchscreen.h>
#include <SPI.h>


#define CS_PIN 33
SPIClass touchSPI(HSPI);
TFT_eSPI tft = TFT_eSPI();
XPT2046_Touchscreen touch(CS_PIN);





void setup()
  {
    Serial.begin(115200);

    tft.begin();
    tft.setRotation(1);
    pinMode(TFT_BL, OUTPUT);
    digitalWrite(TFT_BL, HIGH);
    touchSPI.begin(25, 39, 32, CS_PIN); // CLK, MISO, MOSI, CS
    touch.begin(touchSPI);               // <-- важно!

    // LVGL удалён. Здесь можно добавить инициализацию нового UI через LVGL Editor.
  }

static uint32_t lastTick = 0;
void loop() 
{
    lv_tick_inc(millis() - lastTick);
    lastTick = millis();
    lv_timer_handler();
    delay(5);
}
