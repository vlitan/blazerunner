#include <Arduino.h>
#include "sensors.h"

NewPing forwardSonar(frontSensorPin, frontSensorPin, maxDistance);
NewPing rearSonar(rearSensorPin, rearSensorPin, maxDistance);
NewPing leftSonar(leftSensorPin, leftSensorPin, maxDistance);
NewPing rightSonar(rightSensorPin, rightSensorPin, maxDistance);

//sets up pin modes
void setupSensors(){
  //???? nothing to do I guess  
}

//reads sensors and puts raw data in the array, using indexes from directions_e 
void updateSensorDistances(int distances[4]){
  distances[forward] = forwardSonar.ping_cm();
  distances[rear] = rearSonar.ping_cm();
  distances[left] = leftSonar.ping_cm();
  distances[right] = rightSonar.ping_cm();
}

//reads raw data from the array, perfoms hysteresis comparison and updates the states
void updateSensorStates(bool states[4], int distances[4]){
  for (int i = 0; i < 4; i++){
    states[i] = getNextState(distances[i], states[i]);
  }
}

//given the current value and the last state, based on the Thresholds defined in config.h computes next state
bool getNextState(int currentValue, bool lastState){
  if ((currentValue < lowThreshold) && (lastState == freeWay)){
    return (blocked);
  }
  else if ((currentValue < highThreshold) && (lastState == blocked)){
    return (freeWay);
  }
  return (lastState);
}

