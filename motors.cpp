#include <Arduino.h>
#include "motors.h"



//sets up pin modes for motor pins
void setupMotors(){
  pinMode(leftMotorPinA, OUTPUT);
  pinMode(leftMotorPinB, OUTPUT);
  pinMode(rightMotorPinA, OUTPUT);
  pinMode(rightMotorPinB, OUTPUT);
}
//applies speeds to motors
//TODO not the best code, copy-pasted. refactor
void go(int speedLeft, int speedRight){
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
  go(speed, speed);//TODO compensate
}
//turns 90 degrees to the left / right
void turn(turnDirection_t direction){
  switch (direction){
    case noTurn: turn(0); break;
    case leftTurn: turn(maxSpeed); break;
    case rightTurn: turn(-maxSpeed); break;    
  }
  delay(getCompensatedRotationDelay());
}
//turns a specified amount of degrees
//TODO if it doesn`t turn in place, adjust here.
void turn(int speed){
  go(speed, -speed);
}
//stops motors
void stop(){
  go(0, 0);
}

unsigned int getCompensatedRotationDelay(){
  return (getBatteryVoltage() * 1 * turnDelayMs);
}


