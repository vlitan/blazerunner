#include "motors.h"
#include "sensors.h"
#include "display.h"
#include "sonarStateLeds.h"

int distances[4];
bool sensorStates[4];

void setup() {
 setupMotors();
}

void loop() {
  drive(maxSpeed);
  delay(100);
}
