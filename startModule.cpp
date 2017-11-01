#include <Arduino.h>
#include "startModule.h"
#include "pinConfig.h"
#include "motors.h"
#include "display.h"
extern volatile bool motorsEnabled;

void startModuleSetup(){
  pinMode(startModulePin, INPUT);
  //attachInterrupt(digitalPinToInterrupt(startModulePin), reset, FALLING);
}
void busyWaitForStart(){
  while(stoped());
}
bool stoped(){
  return (!digitalRead(startModulePin));
}
//not working
void reset(){
  displayMessage("stop");
  motorsEnabled = false;
  stop();
}

