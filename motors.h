#pragma once

#include "pinConfig.h"
#include "types.h"
#include "config.h"
#include "batteryChecker.h"

//sets up pin modes for motor pins
void setupMotors();
//applies speeds to motors
void go(int speedLeft, int speedRight);
//goes in a specified direction (forward or backwards)
void drive(driveDirection_t direction);
//drives in a straightline with a specified speed
void drive(int speed);
//turns 90 degrees to the left / right
void turn(turnDirection_t turn);
//turns in place with a speed.
void turn(int speed);
//stops motors
void stop();

