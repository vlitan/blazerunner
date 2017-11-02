#include <Arduino.h>
#include "display.h"
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include "pinConfig.h"
#include "types.h"

LiquidCrystal_I2C lcd(0x27, 16, 2); 

//////////////////////////
char array1[]=" SunFounder               "; //the string to print on the LCD
char array2[]="hello, world!             "; //the string to print on the LCD
int tim = 500; //the value of delay time
int lastDistances[4];

//intializes pins and the dispaly
void setupDisplay(){
  lcd.init(); //initialize the lcd
  lcd.backlight(); //open the backlight 
  lcd.print("asd");
}
void displayYPR(float yaw, float pitch, float roll){
  lcd.clear();
  lcd.setCursor(0,1);
  lcd.print("y:");
  lcd.print((int)yaw);
  lcd.print(" p:");
  lcd.print((int)pitch);
  lcd.print(" r:");
  lcd.print((int)roll);
}

bool changedDistances(int distances[4], int lastDistances[4]){
  for(int i = 0; i < 4; i++){
    if (distances[i] != lastDistances[i]){
      return true;
    }
  }
  return false;
}
//displays 4 integer (distances)
void displayDistances(int distances[4]){
  if (changedDistances(distances, lastDistances)){
      lcd.clear(); //Clears the LCD screen and positions the cursor in the upper-left corner.

      lcd.print("FRNT:");
      lcd.print(distances[front]);
      lcd.setCursor(9, 0);
      
      lcd.print("REAR:");
      lcd.print(distances[rear]);
      lcd.setCursor(9, 1);
      
      lcd.print("LEFT:");
      lcd.print(distances[left]);
      lcd.setCursor(0, 1);
      
      lcd.print("RGHT:");
      lcd.print(distances[right]);
      lcd.setCursor(0, 0);

      for(int i = 0; i < 4; i++){
        lastDistances[i] = distances[i];
      }
  }
}

void displaySensorStates(bool states[4]){
 // if (changedDistances(distances, lastDistances)){
      lcd.clear(); //Clears the LCD screen and positions the cursor in the upper-left corner.

      if (states[front]){
        lcd.print("Fr");
      }
      lcd.setCursor(3, 0);

      if (states[rear]){
        lcd.print("Re");
      }
      lcd.setCursor(6, 0);

      if (states[left]){
        lcd.print("Le");
      }
      lcd.setCursor(9, 0);

      if (states[right]){
        lcd.print("Ri");
      }
      

//      for(int i = 0; i < 4; i++){
//        lastDistances[i] = distances[i];
//      }
//  }
}

void displayMessage(const char * msg){
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print(msg);
}

