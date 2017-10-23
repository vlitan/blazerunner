#include <Arduino.h>
#include "sonarStateLeds.h"
#include "pinConfig.h"
#include "types.h"

void setupSonarStateLeds(){
  pinMode(frontSonarStateLedPin, OUTPUT);
  pinMode(rearSonarStateLedPin, OUTPUT);
  pinMode(rightSonarStateLedPin, OUTPUT);
  pinMode(leftSonarStateLedPin, OUTPUT);
}

void displaySonarState(bool states[4]){
  digitalWrite(frontSonarStateLedPin, !states[front]);
  digitalWrite(rearSonarStateLedPin, !states[rear]);  
  digitalWrite(rightSonarStateLedPin, !states[right]);  
  digitalWrite(leftSonarStateLedPin, !states[left]);  
}

