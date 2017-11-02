#include "motors.h"
#include "sensors.h"
#include "display.h"
#include <LiquidCrystal_I2C.h>
#include "imu.h"
#include "startModule.h"
#include "switches.h"

bool sensorStates[4];
int distances[4];
float yaw;
float pitch;
float roll;
strategy_t strategy;

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

 turn(rightTurn);
 while(1);
}

void loop() {
  //turn(leftTurn);
      //check gyro
    update_ypr(&yaw, &pitch, &roll);
    displayYPR((int)yaw, (int)pitch, (int)roll);
    //delay(1);
//    
//  if (!stopped()){
//    switch(strategy){
//      case testStrat: runTest(); break;
//      case rightWallFollowerStrat: wallFollower(rightTurn); break;
//      case leftWallFollowerStrat: wallFollower(leftTurn); break;
//      case decisionArrayStrat: runDecisionArray(); break;
//      default : runDefault();
//    }
//  }
//  else{
//    stop();
//    displayMessage("stopped");
//    delay(100);
//  }
}

void runDecisionArray(){
  displayMessage("decision array N/A");
  delay(100);
}

void wallFollower(turnDirection_t turn){
  if (turn == rightTurn){
    displayMessage("folllow right");
  }
  else if (turn == leftTurn){
    displayMessage("folllow left");
  }
  else{
    displayMessage("folllow N/A");
  }
  delay(100);
}

void runDefault(){
  displayMessage("defaul strat N/A");
  delay(100);
}

void runTest(){
  static int count = 0;
  if (count < 10){
    //check lcd
    displayMessage("Running test");
  }
  else if (count <= 100){
    //check gyro
    update_ypr(&yaw, &pitch, &roll);
    displayYPR((int)yaw, (int)pitch, (int)roll);
  }
  else if(count <= 200){
    //check sensors
    updateSensorDistances(distances);
    displayDistances(distances);
  }
  else if(count <= 300){
    //check motors
    drive(forwardDrive);
  }
  delay(100);
  count++;
  if (count >= 400){
    stop();
    count = 0;
  }
}

