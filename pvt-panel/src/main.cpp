#include <Arduino.h>
#include <TFT_eSPI.h>
#include <XPT2046_Touchscreen.h>
#include <lvgl.h>
#include "ui/ui.h"   // сгенерирован EEZ-Studio

/* ---------- настройки SPI для тач ---------- */
#define TOUCH_CS 33
SPIClass touchSPI(HSPI);
TFT_eSPI tft = TFT_eSPI();                 // дисплей
XPT2046_Touchscreen touch(TOUCH_CS);       // тач

/* ---------- буферы LVGL ---------- */
#define BUF_LINES 24
static lv_color_t buf1[240 * BUF_LINES];
static lv_color_t buf2[240 * BUF_LINES];

/* ---------- прототипы ---------- */
void my_disp_flush(lv_display_t *disp, const lv_area_t *area, uint8_t *px_map);
void my_touch_read(lv_indev_t *indev, lv_indev_data_t *data);

/* ---------- setup ---------- */
void setup()
{
  Serial.begin(115200);

  /* Инициализация дисплея */
  tft.begin();
  tft.setRotation(3); // usb left
  pinMode(TFT_BL, OUTPUT);
  digitalWrite(TFT_BL, HIGH);

  /* Инициализация тача */
  touchSPI.begin(25, 39, 32, TOUCH_CS); // CLK, MISO, MOSI, CS
  touch.begin(touchSPI);

  /* Инициализация LVGL */
  lv_init();
  lv_display_t *disp = lv_display_create(240, 320);
  lv_display_set_flush_cb(disp, my_disp_flush);
  lv_display_set_buffers(disp, buf1, buf2, sizeof(buf1), LV_DISPLAY_RENDER_MODE_PARTIAL);
  lv_display_set_rotation(disp, LV_DISPLAY_ROTATION_270); // usb left

  lv_indev_t *indev = lv_indev_create();
  lv_indev_set_type(indev, LV_INDEV_TYPE_POINTER);
  lv_indev_set_read_cb(indev, my_touch_read);

  /* Запуск UI из EEZ-Studio */
  ui_init();
  lv_scr_load(objects.main); // добавляем экраны из EEZ-Studio 

  //ui_init();
  create_screens();     // если вдруг не вызвано
  loadScreen(SCREEN_ID_MAIN);



  //lv_obj_set_size(bg, 320, 240);                    // test
  //lv_obj_set_style_bg_color(bg, lv_color_hex(0xFF0000), LV_PART_MAIN); // test
  //lv_obj_center(bg);                   // test                            

// tft.fillScreen(TFT_RED);//test
// delay(1000);//test
  
// --- проверим, жив ли LV-драйвер ---
// lv_obj_t *lbl = lv_label_create(lv_screen_active());
// lv_label_set_text(lbl, "Hello LVGL");
// lv_obj_center(lbl);


}

/* ---------- loop ---------- */
void loop()
{
  lv_timer_handler();
  delay(5);
}

/* ---------- LVGL flush-callback ---------- */
void my_disp_flush(lv_display_t *disp, const lv_area_t *area, uint8_t *px_map)
{
  uint32_t w = area->x2 - area->x1 + 1;
  uint32_t h = area->y2 - area->y1 + 1;
  tft.startWrite();
  tft.setAddrWindow(area->x1, area->y1, w, h);
  tft.pushColors((uint16_t *)px_map, w * h, false);
  tft.endWrite();
  lv_display_flush_ready(disp);
}

/* ---------- LVGL touch-callback ---------- */
void my_touch_read(lv_indev_t *indev, lv_indev_data_t *data)
{
  if (touch.touched())
  {
    TS_Point p = touch.getPoint();
    data->point.x = map(p.y, 600, 3700, 0, 240);
    data->point.y = map(p.x, 420, 3788, 0, 320);
    data->state = LV_INDEV_STATE_PRESSED;
  }
  else
  {
    data->state = LV_INDEV_STATE_RELEASED;
  }
}