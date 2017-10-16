#include <Arduino.h>
#include "stateLeds.h"
#include "pinConfig.h"
#include "types.h"

void setupStateLeds(){
  pinMode(frontStateLedPin, OUTPUT);
  pinMode(rearStateLedPin, OUTPUT);
  pinMode(rightStateLedPin, OUTPUT);
  pinMode(leftStateLedPin, OUTPUT);
}

void displayState(bool states[4]){
  digitalWrite(frontStateLedPin, !states[front]);
  digitalWrite(rearStateLedPin, !states[rear]);  
  digitalWrite(rightStateLedPin, !states[right]);  
  digitalWrite(leftStateLedPin, !states[left]);  
}

