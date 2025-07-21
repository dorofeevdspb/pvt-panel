#include <Arduino.h>
#include <lvgl.h>
#include <TFT_eSPI.h>
#include <XPT2046_Touchscreen.h>

// Удобный каст void* → lv_obj_t*
#define AS_OBJ(x) static_cast<lv_obj_t *>(x)

// Конфигурация дисплея
TFT_eSPI tft = TFT_eSPI();
#define TFT_BL 21

// Аппаратные пины для XPT2046
#define XPT2046_CS   33
#define XPT2046_IRQ  36
#define XPT2046_MOSI 32
#define XPT2046_MISO 39
#define XPT2046_CLK  25

// Размеры экрана
#define TFT_WIDTH  240
#define TFT_HEIGHT 320

// Калибровка тачскрина
#define TS_MINX 220
#define TS_MINY 460
#define TS_MAXX 3700
#define TS_MAXY 3600

// Буфер LVGL
static lv_color_t buf1[TFT_WIDTH * 10];

// Объекты для тачскрина
SPIClass touchSPI(VSPI);
XPT2046_Touchscreen touch(XPT2046_CS);

// Flush callback для дисплея
void my_flush_cb(lv_display_t *disp, const lv_area_t *area, uint8_t *px_map) {
    uint32_t w = lv_area_get_width(area);
    uint32_t h = lv_area_get_height(area);

    tft.startWrite();
    tft.setAddrWindow(area->x1, area->y1, w, h);
    tft.pushColors((uint16_t *)px_map, w * h, true);
    tft.endWrite();

    lv_display_flush_ready(disp);
}

// Touch callback
void my_touch_cb(lv_indev_t *indev, lv_indev_data_t *data) {
    if (touch.touched()) {
        TS_Point p = touch.getPoint();
        data->point.x = map(p.x, TS_MINX, TS_MAXX, 0, TFT_WIDTH);
        data->point.y = map(p.y, TS_MINY, TS_MAXY, 0, TFT_HEIGHT);
        data->state = LV_INDEV_STATE_PRESSED;
    } else {
        data->state = LV_INDEV_STATE_RELEASED;
    }
}

void setup() {
    Serial.begin(115200);

    // Инициализация дисплея
    tft.begin();
    tft.setRotation(2);
    pinMode(TFT_BL, OUTPUT);
    digitalWrite(TFT_BL, HIGH);

    // Инициализация тачскрина через отдельную SPI-шину
    touchSPI.begin(XPT2046_CLK, XPT2046_MISO, XPT2046_MOSI, XPT2046_CS);
    touch.begin(touchSPI);

    // Инициализация LVGL
    lv_init();

    // Настройка дисплея
    lv_display_t *disp = lv_display_create(TFT_WIDTH, TFT_HEIGHT);
    lv_display_set_flush_cb(disp, my_flush_cb);
    lv_display_set_buffers(disp, buf1, NULL, sizeof(buf1), LV_DISPLAY_RENDER_MODE_PARTIAL);

    // Настройка тачскрина
    lv_indev_t *indev = lv_indev_create();
    lv_indev_set_type(indev, LV_INDEV_TYPE_POINTER);
    lv_indev_set_read_cb(indev, my_touch_cb);

    // Пример кнопки
    lv_obj_t *btn = lv_btn_create(lv_screen_active());
    lv_obj_center(btn);
    lv_obj_t *label = lv_label_create(btn);
    lv_label_set_text(label, "Hello");
}

void loop() {
    lv_timer_handler();  // Обработка LVGL
    delay(5);
}
