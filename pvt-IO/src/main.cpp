#include <Arduino.h>

// --- Настройки ---
constexpr uint8_t PIN_PRESSURE = A0; // PC0 - P-sens (MPXV5050DP)
constexpr uint8_t PIN_VALVE    = 7;  // PD7 - valve

String uartBuffer;
unsigned long lastCharAt = 0;

void setup() {
  Serial.begin(115200);
  pinMode(PIN_PRESSURE, INPUT);
  pinMode(PIN_VALVE, OUTPUT);
  digitalWrite(PIN_VALVE, LOW); // по умолчанию клапан закрыт
  // Маркер готовности, чтобы проверить соединение в Serial Monitor
  Serial.println(F("D00"));
}

void handleCommand(const String& cmd) {
  if (cmd == "D11") {
    int raw = analogRead(PIN_PRESSURE);
    Serial.print("D12(");
    Serial.print(raw);
    Serial.println(")");
  } else if (cmd == "D33") { // открыть клапан
    digitalWrite(PIN_VALVE, HIGH);
  } else if (cmd == "D34") { // закрыть клапан
    digitalWrite(PIN_VALVE, LOW);
  }
  // Здесь можно добавить обработку других команд
}

void loop() {
  // Чтение команд из UART
  while (Serial.available()) {
    char c = Serial.read();
    if (c == '\n' || c == '\r') {
      if (uartBuffer.length() > 0) {
        handleCommand(uartBuffer);
        uartBuffer = "";
      }
    } else {
      uartBuffer += c;
    }
    lastCharAt = millis();
  }

  // Обработка команды без перевода строки по таймауту (если терминал не добавляет CR/LF)
  if (uartBuffer.length() > 0 && (millis() - lastCharAt) > 100) {
    String cmd = uartBuffer; cmd.trim();
    if (cmd.length() > 0) handleCommand(cmd);
    uartBuffer = "";
  }
}