#pragma once

const int maxSpeed = 255;
const int turnDelayMs = 1090;
const int driveAfterTurnDelayMs = 3300;
//configure sonar sensors and decision levels.
//TODO change those accordingly
const int maxDistance = 30;
const int lowThreshold = 14; 
const int highThreshold = 16;
const int singleThreshold = 13;
const int sensorDifferenceCompensation = 2;

const int motorSpeedCompesation = 0;

const float lowVoltageThreshold = 100;//TODO
