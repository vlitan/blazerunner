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
  rightTurn,
  roundTurn
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
  decisionArrayStratLeft,
  decisionArrayStratRight,
  noStrat
} strategy_t;

typedef enum action_e{
  forwardAction,
  turnRightAction,
  turnLeftAction,
  dtdRightAction,
  dtdLeftAction,
  roundTurnAction
} action_t;

typedef struct eventDecision_s{
  bool states[4];
  action_t action;
} eventDecision_t;

//used for representing sensor states as boolean values
//TODO this could also be an enum .. (??)
const bool blocked = false;
const bool freeToGo = !blocked; // TODO TODO TODO change name

