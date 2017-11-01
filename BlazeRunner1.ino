#include "motors.h"
#include "sensors.h"
#include "display.h"
#include <LiquidCrystal_I2C.h>
#include "imu.h"
#include "startModule.h"

bool sensorStates[4];
int distances[4];
float yaw;
float pitch;
float roll;

void setup() {
 setupMotors();
 mpu_setup(220, 76, -85, 1788);
 setupDisplay();
 setupSensors();
 startModuleSetup();
 displayMessage("waiting for start");
 busyWaitForStart();
}



void loop() {
  runTest();
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
    displayYPR(yaw, pitch, roll);
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

