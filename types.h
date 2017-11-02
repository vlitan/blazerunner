#pragma once
//used for representing indexes of values belonging to sensors
//and also general purpose directions
//TODO backward of rear >>!>!>??!
typedef enum direction_e{
  front = 0,
  rear,
  left,
  right
} direction_t;

//used for representing turining directions
typedef enum turnDirection_e{
  noTurn,
  leftTurn,
  rightTurn
} turnDirection_t;

//used for representing driving directions
typedef enum driveDirection_e{
  forwardDrive,
  backwardDrive
} driveDirection_t;

typedef enum strategy_e{
  testStrat,
  rightWallFollowerStrat,
  leftWallFollowerStrat,
  decisionArrayStrat
} strategy_t;

//used for representing sensor states as boolean values
//TODO this could also be an enum .. (??)
const bool blocked = false;
const bool freeToGo = !blocked; // TODO TODO TODO change name

