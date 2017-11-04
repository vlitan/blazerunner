#include "motors.h"
#include "sensors.h"
#include "display.h"
#include <LiquidCrystal_I2C.h>
#include "imu.h"
#include "startModule.h"
#include "switches.h"

bool  sensorStates[4];
int   distances[4];
float yaw;
float pitch;
float roll;
strategy_t strategy;

extern NewPing frontSonar;
extern NewPing rearSonar;
extern NewPing leftSonar;
extern NewPing rightSonar;

eventDecision_t decisions[100] = 
{// front       rear      left      right  
  {{freeToGo, freeToGo, freeToGo, freeToGo}, forwardAction},
  {{freeToGo, freeToGo, freeToGo, blocked}, turnLeftAction}
};

void setup() {
  Serial.begin(9600);
  setupMotors();
  mpu_setup(220, 76, -85, 1788);
  setupDisplay();
  setupSensors();
  setupStartModule();
  setupSwitches();
  displayMessage("waiting for start");
  busyWaitForStart();
  strategy = getStrategy();
}

void loop() {
    if (!stopped()){
      switch(strategy){
        case testStrat: runTest(); break;
        case rightWallFollowerStrat: wallFollower(rightTurn); break;
        case leftWallFollowerStrat: wallFollower(leftTurn); break;
        case decisionArrayStrat: runDecisionArray(); break;
        default : runDefault();
      }
    }
    else{
      stop();
      displayMessage("stopped");
      delay(100);
    }
}

void runDecisionArray() {
  displayMessage("decision array N/A");
  static int decisionIndex = 0;
  
  updateSensorDistances(distances);
  updateSensorStates(sensorStates, distances);
  if(decisionMatch(decisions[decisionIndex].states, sensorStates)){
    switch(decisions[decisionIndex].action){
      case forwardAction:   drive(forwardDrive); break;
      case turnRightAction: turn(rightTurn); break;
      case turnLeftAction:  turn(leftTurn); break;
      case dtdRightAction:  driveTurnDrive(rightTurn, forwardDrive); break;
      case dtdLeftAction:   driveTurnDrive(leftTurn, forwardDrive); break;
      case roundTurnAction: turn(roundTurn); break;
    }
  }
}

void wallFollower(turnDirection_t defaultTurn) {
  if (defaultTurn == rightTurn) {
    //displayMessage("folllow right");
    if (getState(NewPing::convert_cm(rightSonar.ping_median(2))) == freeToGo){
      displayMessage("turning right");
      driveTurnDrive(rightTurn, forwardDrive);
    }
    else if(getState(NewPing::convert_cm(frontSonar.ping_median(2))) == freeToGo){
      displayMessage("going forward");
      drive(forwardDrive);
    }
    else if(getState(NewPing::convert_cm(leftSonar.ping_median(2))) == freeToGo){
      displayMessage("tight turn left");
      turn(leftTurn);
    }
    else if(getState(NewPing::convert_cm(rearSonar.ping_median(2))) == freeToGo){
      displayMessage("turning around");
      turn(roundTurn);
    }
    else{
      stop();
      displayMessage("WTF");
    }
  }
  else if (defaultTurn == leftTurn) {
    if (getState(NewPing::convert_cm(leftSonar.ping_median(2))) == freeToGo){
      displayMessage("turning left");
      driveTurnDrive(leftTurn, forwardDrive);
    }
    else if(getState(NewPing::convert_cm(frontSonar.ping_median(2))) == freeToGo){
      displayMessage("going forward");
      drive(forwardDrive);
    }
    else if(getState(NewPing::convert_cm(rightSonar.ping_median(2))) == freeToGo){
      displayMessage("tight turn right");
      turn(rightTurn);
    }
    else if(getState(NewPing::convert_cm(rearSonar.ping_median(2))) == freeToGo){
      displayMessage("turning around");
      turn(roundTurn);
    }
    else{
      stop();
      displayMessage("WTF");
    }
  }
  else {
    displayMessage("folllow N/A");
  }
}

void runDefault() {
  displayMessage("defaul strat N/A");
  delay(100);
}

void runTest() {
  static int count = 0;
  if (count < 10) {
    //check lcd
    displayMessage("Running test");
  }
  else if (count <= 100) {
    //check gyro
    update_ypr(&yaw, &pitch, &roll);
    displayYPR((int)yaw, (int)pitch, (int)roll);
  }
  else if (count <= 300) {
    //check sensors
    updateSensorDistances(distances);
    displayDistances(distances);
  }
  else if (count <= 400) {
    //check motors
    drive(forwardDrive);
  }
  delay(100);
  count++;
  if (count >= 500) {
    stop();
    count = 0;
  }
}


bool decisionMatch(bool actualStates[4], bool targetStates[4]){
  for (int i = 0;i < 4; i++){
    if (actualStates[i] != targetStates[i]){
      return false;
    }
  }
  return true;
}

