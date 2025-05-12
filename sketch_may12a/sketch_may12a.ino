#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "Nader";
const char* password = "Nader2233";
const char* serverUrl = "http://192.168.100.33:3000/api/data";  // Laptop IP address

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi connected");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(serverUrl);
    http.addHeader("Content-Type", "application/json");

    int heartRate = random(60, 130);
    float spo2 = random(9000, 10000) / 100.0;

    String json = "{\"heartRate\":" + String(heartRate) + ",\"spo2\":" + String(spo2) + "}";
    int code = http.POST(json);

    if (code > 0) {
      String response = http.getString();
      Serial.println("Full Response: " + response);

      // Extract status from JSON: {"status":"Normal"}
      int startIndex = response.indexOf(":\"") + 2;
      int endIndex = response.indexOf("\"", startIndex);
      String status = response.substring(startIndex, endIndex);

      Serial.println("Predicted Status: " + status);

      // Example logic (you can hook a buzzer/LED here)
      if (status == "Tachycardia") {
        Serial.println("Warning: High Heart Rate!");
      } else if (status == "Hypoxia") {
        Serial.println("Warning: Low SpO2!");
      } else {
        Serial.println("Vitals Normal.");
      }
    } else {
      Serial.println("POST Failed");
    }

    http.end();
  }

  delay(10000); // Wait 10 seconds before next reading
}
