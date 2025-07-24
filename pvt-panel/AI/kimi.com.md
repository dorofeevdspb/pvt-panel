# KIMI.COM

[kimi.com](kimi.com)

***START***

```

диалог на русском.
в коде очень подробные коментарии на русском языке
hardware:
  board: esp32_2432s028Rv3
  version: cyd2usb

ONLY LVGL 9.3.0


```



platformio.ini
```

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
  https://github.com/lvgl/lvgl.git#v9.3.0
  bodmer/TFT_eSPI@^2.5.43
  https://github.com/PaulStoffregen/XPT2046_Touchscreen.git
 
build_flags =
  -DLV_CONF_SKIP=1
  -DLV_USE_TFT_ESPI=1
  -DUSER_SETUP_LOADED=1
  -DST7789_DRIVER=1
  -DTFT_WIDTH=240
  -DTFT_HEIGHT=320
  -DTFT_MISO=12
  -DTFT_MOSI=13
  -DTFT_SCLK=14
  -DTFT_CS=15
  -DTFT_DC=2
  -DTFT_RST=-1
  -DTFT_BL=21
  -DTFT_BACKLIGHT_ON=HIGH
  -DSPI_FREQUENCY=27000000
  -DTFT_RGB_ORDER=TFT_BGR
  -DTOUCH_CS=33 ; <-- важно! пин сенсора
 

```

одну сенсорную кнопку по центру сенсорного дисплея с надписью "TOUCH",
меняет цвет по нажатию с #FF0000 на  #0000FF,
по нажатию отправляет по uart строку #FF0000 или  #0000FF соответствено


________
***THEEND***

