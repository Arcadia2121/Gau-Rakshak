#ifndef UI_DISPLAY_H
#define UI_DISPLAY_H

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void initDisplay() {
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("OLED Allocation Failed! Check SDA/SCL."));
    for (;;);
  }
  
  // Boot Splash Screen
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.drawRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, SSD1306_WHITE);
  display.setCursor(12, 16);
  display.println(F("SIH26109 SYSTEM"));
  display.setCursor(12, 30);
  display.println(F("BoviCare Edge AI"));
  display.setCursor(12, 44);
  display.println(F("Model: 800-Dataset"));
  display.display();
  delay(2500);
}

void renderTelemetry(float ec, float tempC, float riskScore, String riskCategory) {
  display.clearDisplay();
  
  // Header
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(4, 0);
  display.println(F("EDGE AI INFERENCE"));
  display.drawLine(0, 9, SCREEN_WIDTH, 9, SSD1306_WHITE);

  // Sensor Telemetry
  display.setCursor(0, 14);
  display.printf("EC   : %.2f mS/cm", ec);
  display.setCursor(0, 26);
  display.printf("Temp : %.1f C", tempC);

  // AI Probability
  display.setCursor(0, 38);
  display.printf("Risk : %.1f%%", riskScore);

  // 4-Tier Status Banner (High risk inverts OLED colors)
  if (riskCategory == "HIGH RISK") {
    display.fillRect(0, 50, SCREEN_WIDTH, 14, SSD1306_WHITE);
    display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
    display.setCursor(6, 53);
    display.println(F("STATUS: HIGH RISK!"));
  } else {
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(6, 53);
    display.print(F("STATUS: "));
    display.println(riskCategory);
  }

  display.display();
}

#endif
