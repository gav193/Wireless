#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <EEPROM.h>

const char* ssid = "kylogav";
const char* password = "091097";

AsyncWebServer server(80);

// EEPROM addresses for ON and OFF durations
#define EEPROM_SIZE 64
#define ON_TIME_ADDR 0
#define OFF_TIME_ADDR 4

void setup() {
  Serial.begin(115200);

  // Initialize EEPROM
  EEPROM.begin(EEPROM_SIZE);

  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  Serial.println(WiFi.localIP());

  // Serve HTML form
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/html",
                  "<!DOCTYPE HTML>"
                  "<html>"
                  "<h1>LED Blink Parameters</h1>"
                  "<form action=\"/set\" method=\"GET\">"
                  "ON Duration (ms): <input type=\"number\" name=\"onTime\"><br>"
                  "OFF Duration (ms): <input type=\"number\" name=\"offTime\"><br>"
                  "<input type=\"submit\" value=\"Set\">"
                  "</form>"
                  "</html>");
  });

  // Handle form submission
  server.on("/set", HTTP_GET, [](AsyncWebServerRequest *request) {
    String onTime = request->getParam("onTime")->value();
    String offTime = request->getParam("offTime")->value();

    // Save to EEPROM
    EEPROM.writeInt(ON_TIME_ADDR, onTime.toInt());
    EEPROM.writeInt(OFF_TIME_ADDR, offTime.toInt());
    EEPROM.commit();

    Serial.println("Parameters Saved:");
    Serial.print("ON Duration: ");
    Serial.println(onTime);
    Serial.print("OFF Duration: ");
    Serial.println(offTime);

    request->send(200, "text/html",
                  "<!DOCTYPE HTML>"
                  "<html>"
                  "<h1>Parameters Saved</h1>"
                  "<p>ON Duration: " + onTime + " ms</p>"
                  "<p>OFF Duration: " + offTime + " ms</p>"
                  "</html>");
  });

  // Start server
  server.begin();
}

void loop() {}
