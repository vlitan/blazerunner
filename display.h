#pragma once

//intializes pins and the dispaly
void setupDisplay();
//displays 4 integer (distances)
void displayDistances(int distances[4]);
void displayYPR(float yaw, float pitch, float roll);
void displayMessage(const char * msg);

