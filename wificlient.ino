#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "mySSID"; // Replace with your Wi-Fi SSID
const char* pass = "myPass"; // Replace with your Wi-Fi Password
const char* url = "http://example.com"; // Replace with your target URL

void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi
  Serial.print("Connecting to Wi-Fi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);

  // Wait until connected
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print('.');
  }

  Serial.println("\nConnected to Wi-Fi!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // Perform an HTTP GET request
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    Serial.print("Connecting to website: ");
    Serial.println(url);

    http.begin(url); // Specify the URL
    int httpCode = http.GET(); // Send the GET request

    // Check the HTTP response code
    if (httpCode > 0) {
      Serial.printf("HTTP Response Code: %d\n", httpCode);
      String payload = http.getString(); // Get the response payload
      Serial.println("Response:");
      Serial.println(payload);
    } else {
      Serial.printf("HTTP GET request failed, error: %s\n", http.errorToString(httpCode).c_str());
    }

    http.end(); // Free resources
  } else {
    Serial.println("Wi-Fi is not connected.");
  }

  Serial.println("Exiting setup()...");
}

void loop() {
  // Add code here if you need to perform additional tasks in the main loop
  delay(1000);
}
