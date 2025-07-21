hardware:
  board: esp32_2432s028
  version: cyd2usb
  display:
    driver: ST7789
    size: 240x320
    interface: SPI
    backlight_pin: 21
    rotation: 2
  touch:
    driver: XPT2046
    interface: SPI
    spi_pins:
      irq: 36
      mosi: 32
      miso: 39
      clk: 25
      cs: 33




software:
  os: Windows 11
  ide: VSCode
  platformio:
    platform: espressif32
    board: esp32dev
    framework: arduino
    monitor_speed: 115200
    lib_deps:
      - lvgl/lvgl@^9.3.0
      - bodmer/TFT_eSPI@^2.5.43
      - https://github.com/PaulStoffregen/XPT2046_Touchscreen.git

lvgl:
  version: 9.3.0
  flush_callback: my_flush_cb
  touch_callback: my_touch_cb
  display:
    render_mode: LV_DISPLAY_RENDER_MODE_PARTIAL
    buffer_height: 10
  input_device:
    type: pointer

ui:
  button:
    position: center
    behavior:
      - toggles color between red and blue
      - uses ButtonState struct with "is_red" flag
      - changes style using lv_palette_main
      - logs click to Serial

code:
  language: cpp
  macros:
    - define: AS_OBJ(x)
      value: static_cast<lv_obj_t *>(x)
  notes:
    - avoid deprecated LVGL 8 API
    - support safe casting and minimal memory use

optional:
  tft_espi:
    setup_file: User_Setup.h or User_Setups/SetupXX.h
    spi_pins:
      sck: 14
      mosi: 13
      dc: 2
      cs: 15
      rst: 12
    touch_cs: 5












