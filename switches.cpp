#include <Arduino.h>
#include "pinConfig.h"
#include "switches.h"
#include "types.h"

void  setupSwitches(){
  pinMode(oneSwitchPin, INPUT_PULLUP);
  pinMode(secondSwitchPin, INPUT_PULLUP);
  pinMode(thirdSwitchPin, INPUT_PULLUP);
}

strategy_t getStrategy(){
  int nr = digitalRead(oneSwitchPin) << 2 | digitalRead(secondSwitchPin) << 1;
  switch(nr){
    case 0: return testStrat;
    case 1: return rightWallFollowerStrat;
    case 2: return leftWallFollowerStrat;
    case 3: return decisionArrayStrat;
  }
  return testStrat;
}

