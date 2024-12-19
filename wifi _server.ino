#include <WiFi.h>

// WiFi credentials
const char* ssid = "kylogav";
const char* password = "091097";

// Create a web server object
WiFiServer server(80);

void setup() {
  Serial.begin(115200);

  // Connect ESP32 as a WiFi client
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Start the server
  server.begin();
  Serial.println("WiFiServer started");
  Serial.println(WiFi.localIP());
}

void loop() {
  WiFiClient client = server.available();
  if (client) {
    Serial.println("New Client Connected");
    String request = client.readStringUntil('\r');
    Serial.println(request);
    client.flush();

    // Send HTML response
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("Connection: close");
    client.println();
    client.println("<!DOCTYPE HTML>");
    client.println("<html>");
    client.println("<h1>ESP32 Wireless</h1>");
    client.println("<p>Stefen Sutandi</p>");
    client.println("<p>NIM: 13222091</p>");
    client.println("<p>Pierre Gavin Tan</p>");
    client.println("<p>NIM: 13222097</p>");
    client.println("</html>");
    client.stop();
    Serial.println("Client Disconnected");
  }
}
