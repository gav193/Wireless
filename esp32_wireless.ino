#include <WiFi.h>
#include <WiFiClient.h>
#include <ESPAsyncWebServer.h>
#include <EEPROM.h>

// Replace with your WiFi credentials
const char* ssid = "kylogav";
const char* password = "091097";

// Variables for LED blinking
int ledPin = 2; // Built-in LED
int blinkOnTime = 500; // Default ON duration in ms
int blinkOffTime = 500; // Default OFF duration in ms

// Bluetooth variables
#include <BluetoothSerial.h>
BluetoothSerial SerialBT;

// Web server objects
AsyncWebServer server(80);
WiFiServer wifiServer(80);

// EEPROM settings
#define EEPROM_SIZE 64

// Function to blink LED
void blinkLED() {
  digitalWrite(ledPin, HIGH);
  delay(blinkOnTime);
  digitalWrite(ledPin, LOW);
  delay(blinkOffTime);
}

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);

  // Initialize Bluetooth
  SerialBT.begin("ESP32_Bluetooth"); // Bluetooth device name
  Serial.println("Bluetooth Started");

  // Initialize EEPROM
  EEPROM.begin(EEPROM_SIZE);

  // Load blink parameters from EEPROM
  blinkOnTime = EEPROM.read(0) * 10; // Stored as multiples of 10 ms
  blinkOffTime = EEPROM.read(1) * 10;
  if (blinkOnTime == 0) blinkOnTime = 500; // Default if EEPROM is empty
  if (blinkOffTime == 0) blinkOffTime = 500;

  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");

  // Start web servers
  server.on("/", HTTP_GET, [](AsyncWebServerRequest* request) {
    request->send(200, "text/html", "Name: Stefen Sutandi<br>NIM: 13222091<br>Gavin Tan<br>NIM: 13222097");
  });

  server.on("/form", HTTP_GET, [](AsyncWebServerRequest* request) {
    String htmlForm = "<form action='/set' method='GET'>"
                      "ON Duration (ms): <input type='text' name='on'><br>"
                      "OFF Duration (ms): <input type='text' name='off'><br>"
                      "<input type='submit' value='Set'>"
                      "</form>";
    request->send(200, "text/html", htmlForm);
  });

  server.on("/set", HTTP_GET, [](AsyncWebServerRequest* request) {
    if (request->hasParam("on") && request->hasParam("off")) {
      blinkOnTime = request->getParam("on")->value().toInt();
      blinkOffTime = request->getParam("off")->value().toInt();

      // Save parameters to EEPROM
      EEPROM.write(0, blinkOnTime / 10);
      EEPROM.write(1, blinkOffTime / 10);
      EEPROM.commit();

      request->send(200, "text/html", "Parameters updated!");
    } else {
      request->send(400, "text/html", "Invalid input");
    }
  });

  server.begin();

  // WiFi server (for name and NIM)
  wifiServer.begin();

  // Configure Access Point
  WiFi.softAP("Kelompok_19", "12345678");
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);
}

void loop() {
  // Bluetooth communication
  if (SerialBT.available()) {
    char received = SerialBT.read();
    if (received == '1') {
      digitalWrite(ledPin, HIGH);
      SerialBT.println("LED ON");
    } else if (received == '0') {
      digitalWrite(ledPin, LOW);
      SerialBT.println("LED OFF");
    }
  }

  // Blink LED based on parameters
  blinkLED();

  // Handle WiFi client
  WiFiClient client = wifiServer.available();
  if (client) {
    client.println("Name: Stefen Sutandi");
    client.println("NIM: 13222091");
    client.println("Name: Pierre Gavin Tan");
    client.println("NIM: 13222097");
    client.stop();
  }
}
