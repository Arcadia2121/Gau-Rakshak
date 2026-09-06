#ifndef AI_ENGINE_H
#define AI_ENGINE_H

#include "config.h"
#include <math.h>

// Embedded TinyML Logistic Regression Engine
float runTinyMLInference(float ec_mS, float temp_C) {
  // Logit Linear Combination: z = w0 + w1*EC + w2*Temp
  float z = W_BIAS + (W_EC * ec_mS) + (W_TEMP * temp_C);

  // Sigmoid Activation Function -> Probability [0.0 to 1.0]
  float probability = 1.0 / (1.0 + exp(-z));
  
  return probability * 100.0; // Risk Index as Percentage
}

// Classify risk into 4 official SIH categories
String getRiskClassification(float riskScore) {
  if (riskScore >= 75.0) return "HIGH RISK";
  if (riskScore >= 50.0) return "MODERATE RISK";
  if (riskScore >= 25.0) return "LOW RISK";
  return "NO RISK";
}

#endif
