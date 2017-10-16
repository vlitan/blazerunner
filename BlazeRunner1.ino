#include "motors.h"
#include "sensors.h"
#include "display.h"
#include "stateLeds.h"

int distances[4];
bool sensorStates[4];

void setup() {
  // put your setup code here, to run once:
  setupStateLeds();
  sensorStates[rear]= 10;
  sensorStates[left] = 23;
  sensorStates[front] = 2;
  sensorStates[right] = 33;
}

void loop() {
  displayDistances(distances);
  delay(100);
  distances[front] ++;
}
