#include "BluetoothSerial.h"
#define led 25
#define button 32

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` and enable it
#endif

BluetoothSerial SerialBT;
String msg = "";
char incoming;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32"); // Start Bluetooth Serial
  pinMode(led, OUTPUT);
  pinMode(button, INPUT_PULLUP);
  digitalWrite(led, LOW);
}

void loop() {
  // Reading data from Bluetooth
  if (SerialBT.available()) {
    incoming = SerialBT.read();
    if (incoming != '\n') {
      msg += incoming;
    } else {
      // Process message when newline is received
      if (msg == "led_on") {
        digitalWrite(led, HIGH);
      } else if (msg == "led_off") {
        digitalWrite(led, LOW);
      }
      msg = ""; // Reset the message
    }
    Serial.write(incoming); // Echo the received character
  }

  // Checking button state
  if (digitalRead(button) == LOW) {
    SerialBT.write("Button pressed on ESP32.");
  }

  delay(100); // Delay to avoid rapid looping
}
