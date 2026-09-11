#ifndef CONFIG_H
#define CONFIG_H

// --- 0. BLYNK CLOUD CREDENTIALS ---
// (Must be the very first thing in the file)
#define BLYNK_TEMPLATE_ID   "TMPLxxxxxx"
#define BLYNK_TEMPLATE_NAME "Gau Rakshak"
#define BLYNK_AUTH_TOKEN    "YOUR_BLYNK_AUTH_TOKEN"

// --- 1. HARDWARE PIN DEFINITIONS ---
#define ONE_WIRE_BUS 4        // DS18B20 Temp Data -> GPIO 4
#define TDS_PIN 34            // Analog TDS Sensor -> GPIO 34
#define ALERT_LED_PIN 2       // ESP32 Onboard Blue LED

// --- 2. ADC & VOLTAGE SPECIFICATIONS ---
#define VREF 3.3              // ESP32 Operating Voltage
#define ADC_RESOLUTION 4095.0 // 12-bit ADC (0 - 4095)

// --- 3. WI-FI & GOOGLE CLOUD CONFIGURATION ---
const char* WIFI_SSID     = "YOUR_HOTSPOT_NAME";     
const char* WIFI_PASSWORD = "YOUR_HOTSPOT_PASSWORD"; 

// Paste your Google Apps Script Web App URL here:
const String WEB_APP_URL  = "https://script.google.com/macros/s/YOUR_SCRIPT_ID/exec";

// --- 4. TINYML WEIGHTS (Trained on 800-Row Clinical Dataset) ---
const float W_BIAS = -122.64; 
const float W_EC   = 2.70;    
const float W_TEMP = 2.90;    

#endif
