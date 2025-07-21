

#include <Arduino.h>
#include <TFT_eSPI.h>
#include <XPT2046_Touchscreen.h>
#include <lvgl.h>

#define TOUCH_CS 33
TFT_eSPI tft = TFT_eSPI();
XPT2046_Touchscreen touch(TOUCH_CS);

// Буфер
static lv_color_t buf[240 * 10];
static lv_draw_buf_t draw_buf;

// Отрисовка
void my_disp_flush(lv_display_t *disp, const lv_area_t *area, uint8_t *px_map) {
  uint32_t w = area->x2 - area->x1 + 1;
  uint32_t h = area->y2 - area->y1 + 1;
  tft.startWrite();
  tft.setAddrWindow(area->x1, area->y1, w, h);
  tft.pushColors((uint16_t *)px_map, w * h, false);
  tft.endWrite();
  lv_display_flush_ready(disp);
}

// Сенсор
void my_touch_read(lv_indev_t *indev, lv_indev_data_t *data) {
  if (touch.touched()) {
    TS_Point p = touch.getPoint();
    data->point.x = map(p.y, 200, 3700, 0, 240);
    data->point.y = map(p.x, 300, 3900, 0, 320);
    data->state = LV_INDEV_STATE_PRESSED;
  } else {
    data->state = LV_INDEV_STATE_RELEASED;
  }
}

// Состояние кнопки
static bool isRed = true;

static void btn_event_cb(lv_event_t *e) {
  isRed = !isRed;
  uint32_t color = isRed ? 0xFF0000 : 0x0000FF;
  lv_obj_t *btn = (lv_obj_t *)lv_event_get_target(e);
  lv_obj_set_style_bg_color(btn, lv_color_hex(color), LV_PART_MAIN);
  Serial.println(isRed ? "#FF0000" : "#0000FF");
}

void setup() {
  Serial.begin(115200);

  tft.begin();
  tft.setRotation(1);
  pinMode(TFT_BL, OUTPUT);
  digitalWrite(TFT_BL, HIGH);
  touch.begin();

  lv_init();

  // ✅ Инициализация draw_buf (6 аргументов!)
  lv_draw_buf_init(&draw_buf, 240, 10, LV_COLOR_FORMAT_RGB565,
                   240 * sizeof(lv_color_t), buf, sizeof(buf));

  lv_display_t *disp = lv_display_create(240, 320);
  lv_display_set_flush_cb(disp, my_disp_flush);
  lv_display_set_draw_buffers(disp, &draw_buf, NULL);

  lv_display_set_rotation(disp, LV_DISPLAY_ROTATION_90); // поворот дисплея

  lv_indev_t *indev = lv_indev_create();
  lv_indev_set_type(indev, LV_INDEV_TYPE_POINTER);
  lv_indev_set_read_cb(indev, my_touch_read);

  // Кнопка
  lv_obj_t *btn = lv_button_create(lv_screen_active());
  lv_obj_set_size(btn, 120, 60);
  lv_obj_center(btn);
  lv_obj_set_style_bg_color(btn, lv_color_hex(0xFF0000), LV_PART_MAIN);
  lv_obj_add_event_cb(btn, btn_event_cb, LV_EVENT_CLICKED, NULL);

  lv_obj_t *label = lv_label_create(btn);
  lv_label_set_text(label, "TOUCH");
  lv_obj_center(label);
}

void loop() {
  lv_timer_handler();
  delay(5);
}
