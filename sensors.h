#ifndef _SENSORS_H_
#define _SENSORS_H_

#include <NewPing.h>
#include "pinConfig.h"
#include "config.h"
#include "types.h"

//sets up pin modes
void setupSensors();
//reads sensors and puts raw data in the array, using indexes from directions_e 
void updateSensorDistances(int distances[4]);
//reads raw data from the array, perfoms hysteresis comparison and updates the states
void updateSensorStates(bool states[4], int distances[4]);
//given the current value and the last state, based on the Thresholds defined in config.h computes next state
bool getNextState(int currentValue, bool lastState);

bool getState(int distance);
#endif
