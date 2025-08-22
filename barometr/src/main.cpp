// Read raw BMP280 registers over I2C and print raw ADC values to UART (Arduino Uno).
#include <Arduino.h>
#include <Wire.h>

// BMP280 I2C addresses (try both)
static constexpr uint8_t BMP280_ADDR_1 = 0x76;
static constexpr uint8_t BMP280_ADDR_2 = 0x77;

// BMP280 registers
static constexpr uint8_t REG_ID        = 0xD0; // should be 0x58 for BMP280
static constexpr uint8_t REG_RESET     = 0xE0; // write 0xB6 to reset
static constexpr uint8_t REG_STATUS    = 0xF3; // bit3 measuring, bit0 NVM update
static constexpr uint8_t REG_CTRL_MEAS = 0xF4; // osrs_t[7:5], osrs_p[4:2], mode[1:0]
static constexpr uint8_t REG_CONFIG    = 0xF5; // t_sb[7:5], filter[4:2], spi3w_en[0]
static constexpr uint8_t REG_PRESS_MSB = 0xF7; // 0xF7..0xF9 press, 0xFA..0xFC temp

// I2C helpers
static bool i2cWrite8(uint8_t addr, uint8_t reg, uint8_t val) {
  Wire.beginTransmission(addr);
  Wire.write(reg);
  Wire.write(val);
  return Wire.endTransmission() == 0;
}

static bool i2cRead(uint8_t addr, uint8_t reg, uint8_t *buf, size_t len) {
  Wire.beginTransmission(addr);
  Wire.write(reg);
  if (Wire.endTransmission(false) != 0) { // repeated start
    return false;
  }
  size_t readN = Wire.requestFrom((int)addr, (int)len, (int)true);
  if (readN != len) return false;
  for (size_t i = 0; i < len; ++i) buf[i] = Wire.read();
  return true;
}

static bool i2cRead8(uint8_t addr, uint8_t reg, uint8_t &val) {
  uint8_t b;
  if (!i2cRead(addr, reg, &b, 1)) return false;
  val = b;
  return true;
}

// Try to find BMP280 address and verify chip id
static uint8_t findBmp280() {
  const uint8_t addrs[2] = {BMP280_ADDR_1, BMP280_ADDR_2};
  for (uint8_t i = 0; i < 2; ++i) {
    uint8_t id = 0;
    if (i2cRead8(addrs[i], REG_ID, id) && id == 0x58) {
      return addrs[i];
    }
  }
  return 0; // not found
}

static bool waitWhileMeasuring(uint8_t addr, uint16_t timeoutMs = 50) {
  uint32_t start = millis();
  while (millis() - start < timeoutMs) {
    uint8_t st = 0;
    if (!i2cRead8(addr, REG_STATUS, st)) return false;
    if ((st & 0x08) == 0) return true; // measuring bit cleared
    delay(2);
  }
  return false; // timeout
}

static uint8_t g_addr = 0;

void setup() {
  Serial.begin(115200);
  // Allow some time for Serial on boards with native USB; on Uno it is instant.
  delay(50);

  Wire.begin();
  // 100kHz is safe; modules often support 400kHz too.
  Wire.setClock(100000);

  g_addr = findBmp280();
  if (g_addr == 0) {
    Serial.println(F("BMP280 not found at 0x76/0x77"));
    return;
  }

  // Optional reset
  i2cWrite8(g_addr, REG_RESET, 0xB6);
  delay(2);

  // Wait for NVM update to complete
  (void)waitWhileMeasuring(g_addr, 10); // status bit0 (im_update) isn't exposed via helper, small delay is fine

  // Set config: filter off, standby irrelevant in forced mode
  i2cWrite8(g_addr, REG_CONFIG, 0x00);

  Serial.print(F("BMP280 detected at 0x"));
  Serial.println(g_addr, HEX);
  Serial.println(F("Streaming raw ADC: P_raw, T_raw"));
}

void loop() {
  if (g_addr == 0) {
    delay(500);
    return;
  }

  // Trigger forced measurement with osrs_t = x1, osrs_p = x1, mode = forced (01)
  // ctrl_meas = 0b001 001 01 = 0x25
  if (!i2cWrite8(g_addr, REG_CTRL_MEAS, 0x25)) {
    Serial.println(F("I2C write error (CTRL_MEAS)"));
    delay(500);
    return;
  }

  // Wait until measuring done
  if (!waitWhileMeasuring(g_addr, 40)) {
    Serial.println(F("Measure timeout"));
    delay(200);
    return;
  }

  uint8_t buf[6] = {0};
  if (!i2cRead(g_addr, REG_PRESS_MSB, buf, 6)) {
    Serial.println(F("I2C read error (data)"));
    delay(200);
    return;
  }

  // Parse 20-bit raw values
  int32_t adc_P = ((int32_t)buf[0] << 12) | ((int32_t)buf[1] << 4) | ((int32_t)buf[2] >> 4);
  int32_t adc_T = ((int32_t)buf[3] << 12) | ((int32_t)buf[4] << 4) | ((int32_t)buf[5] >> 4);

  Serial.print(F("P_raw="));
  Serial.print(adc_P);
  Serial.print(F(", T_raw="));
  Serial.println(adc_T);

  // Modest rate to avoid flooding UART
  delay(200);
}