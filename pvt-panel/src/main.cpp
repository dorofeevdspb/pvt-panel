#include <Arduino.h>
#include <TFT_eSPI.h>
#include <XPT2046_Touchscreen.h>
#include <lvgl.h>
#include <SPI.h>
#include "ui/ui.h"



#define CS_PIN 33   // смотри даташит CYD2USB bkb ESP32-2432S028 R3
SPIClass touchSPI(HSPI);
TFT_eSPI tft = TFT_eSPI();
XPT2046_Touchscreen touch(CS_PIN);


// Буфер
static lv_color_t buf[240 * 10];
static lv_draw_buf_t draw_buf;


// Отрисовка
  void my_disp_flush
       (lv_display_t *disp, const lv_area_t *area, uint8_t *px_map)
    {
      uint32_t w = area->x2 - area->x1 + 1;
      uint32_t h = area->y2 - area->y1 + 1;
      tft.startWrite();
      tft.setAddrWindow(area->x1, area->y1, w, h);
      tft.pushColors((uint16_t *)px_map, w * h, false);
      tft.endWrite();
      lv_display_flush_ready(disp);
    }


// Сенсор
void my_touch_read(lv_indev_t *indev, lv_indev_data_t *data)
  {
    if (touch.touched())
      {
        TS_Point p = touch.getPoint();
        // После поворота экрана LVGL оси меняются местами:
        // x LVGL = y сенсора, y LVGL = x сенсора
        // Диапазоны калибровки подбираются экспериментально
        data->point.x = map(p.y, 600, 3700, 0, 240); // LVGL x (ширина)
        data->point.y = map(p.x, 420, 3788, 0, 320); // LVGL y (высота)
  // Для отладки выводим координаты касания и состояние
  data->state = LV_INDEV_STATE_PRESSED;
      }
    else
      {
        data->state = LV_INDEV_STATE_RELEASED;
      }
  }


// button logic removed from main.cpp; handled elsewhere



void setup()
  {
  Serial.begin(115200);

    tft.begin();
    tft.setRotation(1);
    tft.writecommand(0x20); // Включаем инверсию цветов
    pinMode(TFT_BL, OUTPUT);
    digitalWrite(TFT_BL, HIGH);
    touchSPI.begin(25, 39, 32, CS_PIN); // CLK, MISO, MOSI, CS
    touch.begin(touchSPI);               // <-- важно!

    lv_init();

    // Инициализация draw_buf
    lv_draw_buf_init(&draw_buf, 240, 10, LV_COLOR_FORMAT_RGB565,
                    240 * sizeof(lv_color_t), buf, sizeof(buf));

    lv_display_t *disp = lv_display_create(240, 320);
    lv_display_set_flush_cb(disp, my_disp_flush);
    lv_display_set_draw_buffers(disp, &draw_buf, NULL);
    lv_display_set_rotation(disp, LV_DISPLAY_ROTATION_90); // поворот дисплея 
    // Делаем дисплей дефолтным!
    lv_display_set_default(disp);

    lv_indev_t *indev = lv_indev_create();
    lv_indev_set_type(indev, LV_INDEV_TYPE_POINTER);
    lv_indev_set_read_cb(indev, my_touch_read);

  // UI элементы создаются в модуле UI
  ui_init();
  }

static uint32_t lastTick = 0;
void loop() 
{
    lv_tick_inc(millis() - lastTick);
    lastTick = millis();
  lv_timer_handler();
  ui_tick();
    delay(5);
}
