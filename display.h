#pragma once

//intializes pins and the dispaly
void setupDisplay();
//displays 4 integer (distances)
void displayDistances(int distances[4]);
void displayYPR(int yaw, int pitch, int roll);
void displayMessage(const char * msg);
void displaySensorStates(bool states[4]);
