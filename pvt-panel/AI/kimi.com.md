# KIMI.COM

[kimi.com](kimi.com)

***START***

```cpp

на русском
hardware:
  board: esp32_2432s028
  version: cyd2usb

platformio.ini

[platformio]
src_dir = src
default_envs = cyd

[env:cyd]
platform = espressif32
framework = arduino
board = esp32dev
monitor_speed = 115200
monitor_filters = esp32_exception_decoder
upload_speed = 921600


lib_deps =
  lvgl/lvgl@^9.3.0
  bodmer/TFT_eSPI@^2.5.43
  https://github.com/PaulStoffregen/XPT2046_Touchscreen.git  
  

build_flags =
  -DLV_CONF_SKIP
  -DLV_USE_TFT_ESPI
  -DUSER_SETUP_LOADED
  -DUSE_HSPI_PORT
  -DTFT_MISO=12
  -DTFT_MOSI=13
  -DTFT_SCLK=14
  -DTFT_CS=15
  -DTFT_DC=2
  -DTFT_RST=-1
  -DTFT_BL=21
  -DTFT_BACKLIGHT_ON=HIGH
  -DST7789_DRIVER
  -DTFT_INVERSION_OFF
  -DTFT_RGB_ORDER=TFT_BGR
  -DUSER_SETUP_LOADED
	-DUSE_HSPI_PORT
	-DTFT_MISO=12
	-DTFT_MOSI=13
	-DTFT_SCLK=14
	-DTFT_CS=15
	-DTFT_DC=2
	-DTFT_RST=-1
	-DTFT_BL=21
	-DTFT_BACKLIGHT_ON=HIGH
	-DSPI_FREQUENCY=55000000
	-DSPI_READ_FREQUENCY=20000000
	-DSPI_TOUCH_FREQUENCY=2500000
	-DLOAD_GLCD
	-DLOAD_FONT2
	-DLOAD_FONT4
	-DLOAD_FONT6
	-DLOAD_FONT7
	-DLOAD_FONT8
	-DLOAD_GFXFF
	-DST7789_DRIVER
	-DTFT_RGB_ORDER=TFT_BGR
	-DTFT_INVERSION_OFF


    main.cpp

```


```cpp
#include <SPI.h>
#include <XPT2046_Touchscreen.h>

#define T_CS 33
#define T_IRQ 36

SPIClass touchSPI(HSPI);
XPT2046_Touchscreen touch(T_CS, T_IRQ);

void setup() {
  Serial.begin(115200);
  touchSPI.begin(25, 39, 32, 33); // CLK, MISO, MOSI, CS
  touch.begin(touchSPI);
  Serial.println("Touch test started...");
}

void loop() {
  if (touch.touched()) {
    TS_Point p = touch.getPoint();
    Serial.printf("Raw: x=%d, y=%d, z=%d\n", p.x, p.y, p.z);
  } else {
    Serial.println("No touch");
  }
  delay(200);
}
```


добавь поддержку lvgl9 

одну кнопку по центру меняющую цвет при нажатии,




________
***THEEND***

