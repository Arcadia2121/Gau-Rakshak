# Gau-Rakshak:  Bovine Mastitis Early Forecasting Unit 🐄

**Smart India Hackathon 2026** | **Problem Statement:** SIH26109
**Team:** WattWorks | **Category:** Hardware

---

## 📌 Project Overview
Gau-Rakshak is an offline-first IoT unit designed to predict subclinical bovine mastitis 7-14 days before visible symptoms appear. By measuring milk electrical conductivity (ion leakage) and temperature, an embedded TinyML logistic regression model calculates infection risk instantly. 

It provides real-time, 4-tier risk alerts locally on an OLED for rural farmers, while syncing telemetry to a Google Looker Studio dashboard via a webhook for remote veterinary herd management.

## 🛠️ Technology Stack
* **Hardware:** ESP32 NodeMCU, DS18B20 (Waterproof Temperature), DFRobot Analog TDS (Conductivity), 0.96" I2C OLED Display.
* **Edge AI:** TinyML Logistic Regression (C++).
* **Data Science:** Python, Scikit-Learn, Pandas (Trained on an 800-row clinical dataset).
* **Cloud Infrastructure:** Google Apps Script (REST API Webhook), Google Sheets (Database), Looker Studio (Dashboard).

## 🚀 Key Features
* **Offline-First AI:** Inference happens locally on the ESP32. No internet is required to trigger the physical LED/OLED alarms.
* **Clinical Accuracy:** Model weights are derived from a real-world dataset correlating Somatic Cell Count (SCC) with electrical conductivity.
* **Zero-Maintenance Probes:** Solid-state TDS sensors resist milk-fat fouling and clean instantly with water.

## 🔌 Hardware Wiring Guide
| Sensor | ESP32 Pin | Breadboard Power | Notes |
| :--- | :--- | :--- | :--- |
| **OLED Display** | SCL: D22, SDA: D21 | 3.3V / GND | I2C Protocol |
| **TDS Conductivity** | Analog: D34 | 3.3V / GND | - |
| **DS18B20 Temp** | Data: D4 | 3.3V / GND | Requires 4.7kΩ pull-up resistor to 3.3V |
| **Alert LED** | D2 | - | Uses onboard ESP32 LED |

## 👨‍💻 How to Run
1. Wire the components according to the schematic.
2. Open the `.ino` file in the Arduino IDE.
3. Update the `WIFI_SSID`, `WIFI_PASSWORD`, and `WEB_APP_URL` in the `config.h` tab.
4. Upload to the ESP32 using the standard ESP32 Dev Module board profile.
