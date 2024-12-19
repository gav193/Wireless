#include <WiFi.h>

// Access point name and password
const char* ssid = "kylogav";
const char* password = "091097";

// Create a web server object
WiFiServer server(80);

void setup() {
  Serial.begin(115200);

  // Set ESP32 as an access point
  WiFi.softAP(ssid, password);

  // Print access point information
  IPAddress IP = WiFi.softAPIP();
  Serial.println("Access Point started");
  Serial.print("SSID: ");
  Serial.println(ssid);
  Serial.print("IP Address: ");
  Serial.println(IP);

  // Start the web server
  server.begin();
}

void loop() {
  // Check if a client is connected
  WiFiClient client = server.available();
  if (client) {
    Serial.println("New Client Connected");
    String request = client.readStringUntil('\r');
    Serial.println(request);
    client.flush();

    // Send a simple HTML response
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
