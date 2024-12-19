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

  // Define route for form
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

  // Route to handle form submission
  server.on("/set", HTTP_GET, [](AsyncWebServerRequest *request) {
    String onTime = request->getParam("onTime")->value();
    String offTime = request->getParam("offTime")->value();

    Serial.println("Received Parameters:");
    Serial.print("ON Duration: ");
    Serial.println(onTime);
    Serial.print("OFF Duration: ");
    Serial.println(offTime);

    request->send(200, "text/html",
                  "<!DOCTYPE HTML>"
                  "<html>"
                  "<h1>Parameters Updated</h1>"
                  "<p>ON Duration: " + onTime + " ms</p>"
                  "<p>OFF Duration: " + offTime + " ms</p>"
                  "</html>");
  });

  // Start server
  server.begin();
}

void loop() {}
