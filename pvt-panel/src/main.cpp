#include <Arduino.h>
#include <TFT_eSPI.h>
#include <lvgl.h>
#include "ui/ui.h"      // сгенерирован EEZ-Studio

/* ---------- TFT-eSPI ---------- */
TFT_eSPI tft = TFT_eSPI();

/* ---------- LVGL дисплей-буферы ---------- */
#define BUF_LINES 24
static lv_color_t buf1[240 * BUF_LINES];
static lv_color_t buf2[240 * BUF_LINES];

/* ---------- Переменная для кода EEZ ---------- */
bool isRed = true;

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
    uint16_t x, y;
    data->state = tft.getTouch(&x, &y) ? LV_INDEV_STATE_PRESSED
                                        : LV_INDEV_STATE_RELEASED;
    data->point.x = x;
    data->point.y = y;
}

/* ---------- Инициализация ---------- */
void setup()
{
    Serial.begin(115200);

    tft.begin();
    tft.setRotation(1);          // landscape
    pinMode(TFT_BL, OUTPUT);
    analogWrite(TFT_BL, 180);    // подсветка

   lv_init();
   lv_display_t *disp = lv_display_create(240, 320);
   lv_display_set_flush_cb(disp, my_disp_flush);
   lv_display_set_buffers(disp, buf1, buf2, sizeof(buf1), LV_DISPLAY_RENDER_MODE_PARTIAL);
   lv_display_set_rotation(disp, LV_DISPLAY_ROTATION_90);



    

    lv_indev_t *indev = lv_indev_create();
    lv_indev_set_type(indev, LV_INDEV_TYPE_POINTER);
    lv_indev_set_read_cb(indev, my_touch_read);

    ui_init();   // запуск UI из EEZ-Studio
}

/* ---------- Главный цикл ---------- */
void loop()
{
    lv_timer_handler();
    delay(5);
}