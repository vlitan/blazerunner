#include <Arduino.h>
#include "motors.h"
#include "startModule.h"
#include "imu.h"
#include "display.h"
volatile bool motorsEnabled;

//sets up pin modes for motor pins
void setupMotors(){
  pinMode(leftMotorPinA, OUTPUT);
  pinMode(leftMotorPinB, OUTPUT);
  pinMode(rightMotorPinA, OUTPUT);
  pinMode(rightMotorPinB, OUTPUT);
  motorsEnabled = true;
  stop();
}
//applies speeds to motors
//TODO not the best code, copy-pasted. refactor
void go(int speedLeft, int speedRight){
  if (!stopped()){//check start/stopModule
    if (speedLeft > 0) {
      analogWrite(leftMotorPinA, speedLeft);
      analogWrite(leftMotorPinB, 0);
    } 
    else {
      analogWrite(leftMotorPinA, 0);
      analogWrite(leftMotorPinB, -speedLeft);
    }
   
    if (speedRight > 0) {
      analogWrite(rightMotorPinA, speedRight);
      analogWrite(rightMotorPinB, 0);
    }else {
      analogWrite(rightMotorPinA, 0);
      analogWrite(rightMotorPinB, -speedRight);
    }
  }
  else{
      analogWrite(leftMotorPinB, 0);
      analogWrite(leftMotorPinA, 0);
      analogWrite(rightMotorPinB, 0);
      analogWrite(rightMotorPinA, 0);
  }
}
//goes in a specified direction (forward or backwards)
void drive(driveDirection_t direction){
  switch(direction){
    case forwardDrive: drive(maxSpeed); break;
    case backwardDrive: drive(-maxSpeed); break;
  }
}
//drives in a straightline with a specified speed
//TODO if the robot is not going straight, adjust here
void drive(int speed){
  go(speed - motorSpeedCompesation, speed  - motorSpeedCompesation);//TODO compensate
}
//turns 90 degrees to the left / right
void turn(turnDirection_t direction){
//  float startYaw;
//  float finalYaw;
//  float currentYaw;
//  float pitch;
//  float roll;
  int spinFactor = 1;
  int timeFactor = 1;
  
  //update_ypr(&startYaw, &pitch, &roll);
  switch (direction){
    case noTurn: 
              return;
        break;
    case leftTurn:
              spinFactor = -1;
        break;
    case rightTurn: 
              spinFactor = 1;
         break;
    case roundTurn:
              timeFactor = 2;
         break;  
  }
  unsigned long millisFinish = millis() + turnDelayMs * timeFactor;
  while (millis() < millisFinish){
    turn(maxSpeed * spinFactor);
  }
  stop();
}
//TODO if it doesn`t turn in place, adjust here.
void turn(int speed){
  go(speed, -speed);
}
//stops motors
void stop(){
  go(0, 0);
}

void turnThenDrive(turnDirection_t turnDirection, driveDirection_t driveDirection){
  unsigned long millisFinish = millis() + driveAfterTurnDelayMs / 2;
  while (millis() < millisFinish){
     drive(driveDirection);
  }
  turn(turnDirection);
  millisFinish = millis() + driveAfterTurnDelayMs;
  while (millis() < millisFinish){
     drive(driveDirection);
  }
}



