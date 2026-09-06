#ifndef SENSORS_H
#define SENSORS_H

#include "config.h"
#include <OneWire.h>
#include <DallasTemperature.h>
#include <math.h>

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature tempSensors(&oneWire);

void initSensors() {
  tempSensors.begin();
  analogReadResolution(12);
  analogSetPinAttenuation(TDS_PIN, ADC_11db);
}

// 30-sample median filter to eliminate electrical noise
float getFilteredVoltage(int sampleCount = 30) {
  int samples[sampleCount];
  for (int i = 0; i < sampleCount; i++) {
    samples[i] = analogRead(TDS_PIN);
    delay(2);
  }
  
  // Sort samples
  for (int i = 0; i < sampleCount - 1; i++) {
    for (int j = 0; j < sampleCount - i - 1; j++) {
      if (samples[j] > samples[j + 1]) {
        int temp = samples[j];
        samples[j] = samples[j + 1];
        samples[j + 1] = temp;
      }
    }
  }
  return (float)samples[sampleCount / 2] * VREF / ADC_RESOLUTION;
}

// Read temperature with failsafe check
float readTemperature() {
  tempSensors.requestTemperatures();
  float t = tempSensors.getTempCByIndex(0);
  if (t <= -50.0 || t == DEVICE_DISCONNECTED_C) {
    return 36.0; // Return physiological mean fallback
  }
  return t;
}

// Convert filtered voltage to Electrical Conductivity (mS/cm)
float readConductivity(float tempC) {
  float rawVoltage = getFilteredVoltage();
  
  // Standard non-linear temperature compensation
  float compCoeff = 1.0 + 0.02 * (tempC - 25.0);
  float compVoltage = rawVoltage / compCoeff;
  
  // Convert voltage to TDS (ppm)
  float tds = (133.42 * pow(compVoltage, 3) 
              - 255.86 * pow(compVoltage, 2) 
              + 857.39 * compVoltage) * 0.5;
  if (tds < 0) tds = 0;
  
  // Convert TDS to EC (mS/cm)
  return (tds * 2.0) / 1000.0;
}

#endif
