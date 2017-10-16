#include <Arduino.h>
#include "stateLeds.h"
#include "pinConfig.h"
#include "types.h"

void setupChoiceLeds(){
  pinMode(frontChoiceLedPin, OUTPUT);
  pinMode(rearChoiceLedPin, OUTPUT);
  pinMode(rightChoiceLedPin, OUTPUT);
  pinMode(leftChoiceLedPin, OUTPUT);
}

void shutdownAll(){
    digitalWrite(frontChoiceLedPin, LOW);
    digitalWrite(rearChoiceLedPin, LOW);
    digitalWrite(leftChoiceLedPin, LOW);
    digitalWrite(rightChoiceLedPin, LOW);
}

void lightLed(direction_t direction){
  shutdownAll();
  switch(direction){
    case front: digitalWrite(frontChoiceLedPin, HIGH); break;
    case rear: digitalWrite(rearChoiceLedPin, HIGH); break;
    case left: digitalWrite(leftChoiceLedPin, HIGH); break;
    case right: digitalWrite(rightChoiceLedPin, HIGH); break;
  }
}

