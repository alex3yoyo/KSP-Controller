/* @file ksp_controller.ino
|| @version 1.0
|| @author alex3yoyo
|| @contact alex3yoyo@gmail.com
|| 
|| http://github.com/alex3yoyo/KSP-Controller/
|| 
|| Copyright 2014 alex3yoyo
|| 
|| This program is free software: you can redistribute it and/or modify
|| it under the terms of the GNU General Public License as published by
|| the Free Software Foundation, either version 3 of the License, or
|| (at your option) any later version.
|| 
|| This program is distributed in the hope that it will be useful,
|| but WITHOUT ANY WARRANTY; without even the implied warranty of
|| MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
|| GNU General Public License for more details.
|| 
|| You should have received a copy of the GNU General Public License
|| along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <Wire.h>
#include <Keypad.h>
#include "Adafruit_MCP23008.h"

Adafruit_MCP23008 mcp;

// Arduino pins
const int keyedSwitch = 4;  // Main switch
const int abortButton = 1;
const int stageButton = 2;
const int rcsButton = 7;
const int sasButton = 8;
const int lightsButton = 9;
const int gearButton = 10;
const int brakesButton = 11;
const int cutThrottleButton = 12;

// MCP23008 pins
const int cameraModeButton = 7;
const int cameraViewButton = 6;
const int cameraResetButton = 5;
const int flightUIButton = 4;
const int flightLogButton = 3;
const int orbitalMapButton = 2;
const int warpMinusButton = 1;
const int warpPlusButton = 0;

// 3x4 Matrix Keypad
const byte ROWS = 4; // Four rows
const byte COLS = 3; // Three columns
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
byte rowPins[ROWS] = {8, 7, 6, 5}; // Connect to the row pinouts of the keypad
byte colPins[COLS] = {4, 3, 2}; // Connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );


void setup() {
  // Arduino pins
  pinMode(keyedSwitch, INPUT_PULLUP);
  pinMode(abortButton, INPUT_PULLUP);
  pinMode(stageButton, INPUT_PULLUP);
  pinMode(rcsButton, INPUT_PULLUP);
  pinMode(sasButton, INPUT_PULLUP);
  pinMode(lightsButton, INPUT_PULLUP);
  pinMode(gearButton, INPUT_PULLUP);
  pinMode(brakesButton, INPUT_PULLUP);
  pinMode(cutThrottleButton, INPUT_PULLUP);
  
  // MCP23008 pins
  mcp.begin();
  
  mcp.pinMode(warpPlusButton, INPUT);
  mcp.pullUp(warpPlusButton, HIGH);
  mcp.pinMode(warpMinusButton, INPUT);
  mcp.pullUp(warpMinusButton, HIGH);
  mcp.pinMode(orbitalMapButton, INPUT);
  mcp.pullUp(orbitalMapButton, HIGH);
  mcp.pinMode(flightLogButton, INPUT);
  mcp.pullUp(flightLogButton, HIGH);
  mcp.pinMode(flightLogButton, INPUT);
  mcp.pullUp(flightLogButton, HIGH);
  mcp.pinMode(flightLogButton, INPUT);
  mcp.pullUp(flightLogButton, HIGH);
  mcp.pinMode(flightLogButton, INPUT);
  mcp.pullUp(flightLogButton, HIGH);
  mcp.pinMode(flightUIButton, INPUT);
  mcp.pullUp(flightUIButton, HIGH);
  mcp.pinMode(cameraResetButton, INPUT);
  mcp.pullUp(cameraResetButton, HIGH);
  mcp.pinMode(cameraViewButton, INPUT);
  mcp.pullUp(cameraViewButton, HIGH);
  mcp.pinMode(cameraModeButton, INPUT);
  mcp.pullUp(cameraModeButton, HIGH);
}

void loop() {
  if ((digitalRead(keyedSwitch) == LOW)) {
    // Arduino pins
    if ((digitalRead(abortButton) == LOW)) {
      Keyboard.write('a');
    }
    if ((digitalRead(stageButton) == LOW)) {
      Keyboard.write(' ');
    }
    if ((digitalRead(rcsButton) == LOW)) {
      Keyboard.write('r');
    }
    if ((digitalRead(sasButton) == LOW)) {
      Keyboard.write('t');
    }
    if ((digitalRead(lightsButton) == LOW)) {
      Keyboard.write('u');
    }
    if ((digitalRead(gearButton) == LOW)) {
      Keyboard.write('g');
    }
    if ((digitalRead(brakesButton) == LOW)) {
      Keyboard.write('b');
    }
    if ((digitalRead(cutThrottleButton) == LOW)) {
      Keyboard.write('x');
    }
    
    // MCP23008 pins
    if ((mcp.digitalRead(warpPlusButton) == LOW)) {
      Keyboard.write('+');
    }
    if ((mcp.digitalRead(warpMinusButton) == LOW)) {
      Keyboard.write('-');
    }
    if ((mcp.digitalRead(orbitalMapButton) == LOW)) {
      Keyboard.write('m');
    }
    if ((mcp.digitalRead(flightLogButton) == LOW)) {
      Keyboard.write(KEY_F3);
    }
    if ((mcp.digitalRead(flightUIButton) == LOW)) {
      Keyboard.write(KEY_F2);
    }
    /*if ((mcp.digitalRead(cameraResetButton) == LOW)) {
      Keyboard.write('?');
    }*/
    if ((mcp.digitalRead(cameraViewButton) == LOW)) {
      Keyboard.write('v');
    }
    if ((mcp.digitalRead(cameraModeButton) == LOW)) {
      Keyboard.write('c');
    }
    
    // 3x4 matrix keypad for toggling action groups
    int keypadKey = keypad.getKey();
    if (keypadKey) {
      if ((keypadKey == '1')) {
        Keyboard.write('1');
      }
      if ((keypadKey == '2')) {
        Keyboard.write('2');
      }
      if ((keypadKey == '3')) {
        Keyboard.write('3');
      }
      if ((keypadKey == '4')) {
        Keyboard.write('4');
      }
      if ((keypadKey == '5')) {
        Keyboard.write('5');
      }
      if ((keypadKey == '6')) {
        Keyboard.write('6');
      }
      if ((keypadKey == '7')) {
        Keyboard.write('7');
      }
      if ((keypadKey == '8')) {
        Keyboard.write('8');
      }
      if ((keypadKey == '9')) {
        Keyboard.write('9');
      }
    }
  }
  delay(50);
}
