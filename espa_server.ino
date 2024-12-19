#include <WiFi.h>
#include <ESPAsyncWebServer.h>

// WiFi credentials
const char* ssid = "kylogav";
const char* password = "091097";

// Create an AsyncWebServer object
AsyncWebServer server(80);

void setup() {
  Serial.begin(115200);

  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  Serial.println(WiFi.localIP());

  // Define route
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/html",
                  "<!DOCTYPE HTML>"
                  "<html>"
                  "<h1>ESP32 Wireless</h1>"
                  "<p>Stefen Sutandi</p>"
                  "<p>NIM: 13222091</p>"
                  "<p>Pierre Gavin Tan</p>"
                  "<p>NIM: 13222097</p>"
                  "</html>");
  });

  // Start server
  server.begin();
}

void loop() {}
