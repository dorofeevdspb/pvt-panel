


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


