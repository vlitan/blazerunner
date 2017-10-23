#include <Arduino.h>
#include "batteryChecker.h"
#include "pinConfig.h"
#include "config.h"

void setupBatteryChecker(){
  pinMode(batteryPin, INPUT);
}

bool isBatteryLow(){
  return (getBatteryVoltage() < lowVoltageThreshold);
}

float getBatteryVoltage(){
  return (analogRead(batteryPin) * 1.0f);
}

