#include <Arduino.h>
#include <TFT_eSPI.h>
#include <XPT2046_Touchscreen.h>
#include <lvgl.h>

// ---------- Пины ----------
#define TFT_BL   21
#define T_CS     33
#define T_IRQ    36

// ---------- TFT ----------
TFT_eSPI tft = TFT_eSPI();
#define TFT_WIDTH  240
#define TFT_HEIGHT 320

// ---------- Touch ----------
SPIClass touchSPI = SPIClass(VSPI);
XPT2046_Touchscreen touch(T_CS, T_IRQ);

// ---------- Калибровка тача ----------
#define TOUCH_MIN_X 200
#define TOUCH_MAX_X 3700
#define TOUCH_MIN_Y 240
#define TOUCH_MAX_Y 3800

// ---------- Буфер ----------
static lv_color_t buf1[TFT_WIDTH * 10];

// ---------- Прототипы ----------
void tft_flush_cb(lv_display_t *disp, const lv_area_t *area, uint8_t *px_map);
void touch_read_cb(lv_indev_t *indev, lv_indev_data_t *data);
void button_event_cb(lv_event_t *e);

// ---------- Setup ----------
void setup()
{
  Serial.begin(115200);

  pinMode(TFT_BL, OUTPUT);
  digitalWrite(TFT_BL, HIGH);

  tft.begin();
  tft.setRotation(1); // 0, 1, 2, 3 — подберите под вашу плату

  // Touch
  touchSPI.begin(25, 39, 32, 33); // CLK, MISO, MOSI, CS
  touch.begin(touchSPI);

  // LVGL
  lv_init();

  lv_display_t *disp = lv_display_create(TFT_WIDTH, TFT_HEIGHT);
  lv_display_set_flush_cb(disp, tft_flush_cb);
  lv_display_set_buffers(disp, buf1, nullptr, sizeof(buf1), LV_DISPLAY_RENDER_MODE_PARTIAL);

  lv_indev_t *indev = lv_indev_create();
  lv_indev_set_type(indev, LV_INDEV_TYPE_POINTER);
  lv_indev_set_read_cb(indev, touch_read_cb);

  // Кнопка
  lv_obj_t *btn = lv_btn_create(lv_scr_act());
  lv_obj_set_size(btn, 120, 60);
  lv_obj_center(btn);
  lv_obj_add_event_cb(btn, button_event_cb, LV_EVENT_CLICKED, nullptr);

  lv_obj_t *label = lv_label_create(btn);
  lv_label_set_text(label, "Touch me");
  lv_obj_center(label);
}

// ---------- Loop ----------
void loop()
{
  lv_timer_handler();
  delay(5);
}

// ---------- Flush ----------
void tft_flush_cb(lv_display_t *disp, const lv_area_t *area, uint8_t *px_map)
{
  uint32_t w = area->x2 - area->x1 + 1;
  uint32_t h = area->y2 - area->y1 + 1;
  tft.startWrite();
  tft.setAddrWindow(area->x1, area->y1, w, h);
  tft.pushColors((uint16_t *)px_map, w * h, true);
  tft.endWrite();
  lv_display_flush_ready(disp);
}

// ---------- Touch ----------
void touch_read_cb(lv_indev_t *indev, lv_indev_data_t *data)
{
  if (touch.touched()) {
    TS_Point p = touch.getPoint();
    data->point.x = map(p.x, TOUCH_MIN_X, TOUCH_MAX_X, 0, TFT_HEIGHT);
    data->point.y = map(p.y, TOUCH_MIN_Y, TOUCH_MAX_Y, 0, TFT_WIDTH);
    data->state = LV_INDEV_STATE_PRESSED;
  } else {
    data->state = LV_INDEV_STATE_RELEASED;
  }
}

// ---------- Button ----------
void button_event_cb(lv_event_t *e)
{
  lv_obj_t *btn = (lv_obj_t *)lv_event_get_target(e);
  static lv_color_t colors[] = {
    lv_palette_main(LV_PALETTE_BLUE),
    lv_palette_main(LV_PALETTE_RED),
    lv_palette_main(LV_PALETTE_GREEN)
  };
  static uint8_t idx = 0;
  idx = (idx + 1) % 3;
  lv_obj_set_style_bg_color(btn, colors[idx], LV_PART_MAIN);
}
