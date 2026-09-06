#include "config.h"
#include "sensors.h"
#include "ai_engine.h"
#include "ui_display.h"
#include <WiFi.h>
#include <HTTPClient.h>
#include <BlynkSimpleEsp32.h> // Blynk IoT Library

void setup() {
  Serial.begin(115200);
  
  pinMode(ALERT_LED_PIN, OUTPUT);
  digitalWrite(ALERT_LED_PIN, LOW);

  initSensors();
  initDisplay();

  // Attempt Wi-Fi Connection (Non-blocking for offline mode)
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  
  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 10) {
    delay(500);
    Serial.print(".");
    attempts++;
  }
  
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nWi-Fi Connected!");
    // Initialize Blynk only if Wi-Fi is available
    Blynk.config(BLYNK_AUTH_TOKEN);
  } else {
    Serial.println("\nWi-Fi Offline. Running in standalone Edge mode.");
  }
}

void loop() {
  // 1. Maintain Blynk connection if online
  if (WiFi.status() == WL_CONNECTED) {
    Blynk.run(); 
  }

  // 2. Data Acquisition
  float tempC = readTemperature();
  float ec = readConductivity(tempC);

  // 3. Edge AI Inference
  float riskScore = runTinyMLInference(ec, tempC);
  String riskCategory = getRiskClassification(riskScore);

  // 4. Physical Actuation (Alert LED)
  bool alertActive = (riskScore >= 50.0);
  digitalWrite(ALERT_LED_PIN, alertActive ? HIGH : LOW);

  // 5. Update Local OLED Display
  renderTelemetry(ec, tempC, riskScore, riskCategory);

  // 6. Dual Cloud Sync (Google Sheets + Blynk)
  if (WiFi.status() == WL_CONNECTED) {
    
    // --- SEND TO BLYNK MOBILE APP ---
    Blynk.virtualWrite(V0, ec);          // Map to Gauge V0 in app
    Blynk.virtualWrite(V1, tempC);       // Map to Gauge V1 in app
    Blynk.virtualWrite(V2, riskScore);   // Map to Chart V2 in app
    
    if (riskScore >= 75.0) {
      // Triggers push notification to farmer's phone
      Blynk.logEvent("mastitis_alert", "HIGH RISK: Cow needs immediate checking!"); 
    }

    // --- SEND TO GOOGLE SHEETS WEBHOOK ---
    if (WEB_APP_URL.startsWith("https://")) {
      HTTPClient http;
      String url = WEB_APP_URL + "?ec=" + String(ec, 2) + 
                   "&temp=" + String(tempC, 1) + 
                   "&risk=" + String(riskScore, 1) + 
                   "&status=" + riskCategory;
      
      http.begin(url);
      int responseCode = http.GET();
      if (responseCode > 0) {
        Serial.println("Google Cloud Sync OK");
      }
      http.end();
    }
  }

  delay(2000); // 2-second delay between telemetry cycles
}
