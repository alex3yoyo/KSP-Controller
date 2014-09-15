/* @file ksp_controller.ino
|| @version 1.0
|| @author Alexander Coll
|| @contact me@alexcoll.com
||
|| http://github.com/alexcoll/KSP-Controller/
||
|| Copyright (c) 2014 Alexander Coll
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
#include "Adafruit_MCP23017.h"
#include "Adafruit_RGBLCDShield.h"

Adafruit_MCP23008 mcp;

// Arduino pins
const int mainSwitch = 4;
const int abortButton = 1;
const int stageButton = 0;
const int cutThrottleButton = A0;
const int brakesButton = A5;
const int gearButton = A4;
const int lightsButton = A3;
const int sasButton = A2;
const int rcsButton = A1;

const int arduinoInputPins[] = {mainSwitch, abortButton, stageButton, cutThrottleButton, brakesButton, gearButton, lightsButton, sasButton, rcsButton};

/*
const int gauge0Pin = 12;
const int gauge1Pin = 11;
const int gauge2Pin = 10;

int gauge0Value = 0;
int gauge1Value = 0;
int gauge2Value = 0;
*/

// MCP23008 pins
const int warpPlusButton = 0;
const int warpMinusButton = 1;
const int orbitalMapButton = 2;
const int flightLogButton = 3;
const int flightUIButton = 4;
const int cameraViewButton = 5;
const int cameraModeButton = 6;

const int mcpInputPins[] = {warpPlusButton, warpMinusButton, orbitalMapButton, flightLogButton, flightUIButton, cameraViewButton, cameraModeButton};

// 3x4 Matrix Keypad
const byte ROWS = 4;
const byte COLS = 3;
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};

byte rowPins[ROWS] = {12, 11, 10, 9}; // Connect to the row pinouts of the keypad
byte colPins[COLS] = {8, 7, 6}; // Connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

// Other stuff
const int delayBetweenPressess = 200;
boolean brakesToggled = false;

void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);

  // Arduino pins
  for(int i = 0; i < sizeof(arduinoInputPins); i++) {
    pinMode(arduinoInputPins[i], INPUT_PULLUP);
  }
  pinMode(gauge0Pin, OUTPUT);
  pinMode(gauge1Pin, OUTPUT);
  pinMode(gauge2Pin, OUTPUT);

  // MCP23008 pins
  // Buttons connected to the I/O expander use functions from the Adafruit_MCP23008 library
  mcp.begin();
  for(int i = 0; i < sizeof(mcpInputPins); i++) {
    mcp.pinMode(mcpInputPins[i], INPUT);
    mcp.pullUp(mcpInputPins[i], HIGH);
  }
}

/*
void update_gauges() {
  if (Serial.available()) {
    int valueSurfaceVelocity = Serial.parseInt();
    int valueObritalVelocity = Serial.parseInt();
    int valueVerticalVelocity = Serial.parseInt();

    gauge0Value = Serial.parseInt(); //Looks for the next valid integer in the serial stream
    gauge1Value = Serial.parseInt();
    gauge2Value = Serial.parseInt();
  }
  // look for the newline
  if (Serial.read() == '\n') {
    // constrain the values to 0 - 255
    gauge0Value = constrain(gauge0Pin, 0, 255);
    gauge1Value = constrain(gauge1Pin, 0, 255);
    gauge2Value = constrain(gauge2Pin, 0, 255);

    // Write the values to the display
    analogWrite(gauge0Pin, gauge0Value);
    analogWrite(gauge1Pin, gauge1Value);
    analogWrite(gauge2Pin, gauge2Value);
  }
}
*/

void button_pressed(key, message) {
    Serial.println(message);
    Keyboard.write(key);
    delay(delayBetweenPressess);
}

void loop() {
  while (true) {
    if ((digitalRead(mainSwitch) == LOW)) {
      Keyboard.begin();
      Serial.println("Keyboard emulation started");

      while ((digitalRead(mainSwitch) == LOW)) {
        // Arduino pins
        if ((digitalRead(abortButton) == LOW)) {
          Serial.println("ABORT");
          Keyboard.write(KEY_BACKSPACE);
          delay(delayBetweenPressess);
        }
        if ((digitalRead(stageButton) == LOW)) {
          Serial.println("Staged");
          Keyboard.write(' ');
          delay(delayBetweenPressess);
        }
        if ((digitalRead(rcsButton) == LOW)) {
          Serial.println("RCS toggled");
          Keyboard.write('r');
          delay(delayBetweenPressess);
        }
        if ((digitalRead(sasButton) == LOW)) {
          Serial.println("SAS toggled");
          Keyboard.write('t');
          delay(delayBetweenPressess);
        }
        if ((digitalRead(lightsButton) == LOW)) {
          Serial.println("Lights toggled");
          Keyboard.write('u');
          delay(delayBetweenPressess);
        }
        if ((digitalRead(gearButton) == LOW)) {
          Serial.println("Gear toggled");
          Keyboard.write('g');
          delay(delayBetweenPressess);
        }
        if ((digitalRead(brakesButton) == LOW)) {
          // Brake key must be held down, we will use press and release to do this
          if (brakesToggled == false) {
            Serial.println("Brakes toggled on");
            Keyboard.press('b');
            brakesToggled = true;
            delay(delayBetweenPressess);
          }
          else if (brakesToggled == true) {
            Serial.println("Brakes toggled off");
            Keyboard.release('b');
            brakesToggled = false;
            delay(delayBetweenPressess);
          }
        }
        if ((digitalRead(cutThrottleButton) == LOW)) {
          Serial.println("Cut throttle");
          Keyboard.write('x');
          delay(delayBetweenPressess);
        }

        // MCP23008 pins
        if ((mcp.digitalRead(warpPlusButton) == LOW)) {
          Serial.println("Warp increased");
          Keyboard.write('.');
          delay(delayBetweenPressess);
        }
        if ((mcp.digitalRead(warpMinusButton) == LOW)) {
          Serial.println("Warp decreased");
          Keyboard.write(',');
          delay(delayBetweenPressess);
        }
        if ((mcp.digitalRead(orbitalMapButton) == LOW)) {
          Serial.println("Orbital map toggled");
          Keyboard.write('m');
          delay(delayBetweenPressess);
        }
        if ((mcp.digitalRead(flightLogButton) == LOW)) {
          Serial.println("Flight log toggled");
          Keyboard.write(KEY_F3);
          delay(delayBetweenPressess);
        }
        if ((mcp.digitalRead(flightUIButton) == LOW)) {
          Serial.println("Flight UI toggled");
          Keyboard.write(KEY_F2);
          delay(delayBetweenPressess);
        }
        if ((mcp.digitalRead(cameraViewButton) == LOW)) {
          Serial.println("Camera view changed");
          Keyboard.write('v');
          delay(delayBetweenPressess);
        }
        if ((mcp.digitalRead(cameraModeButton) == LOW)) {
          Serial.println("Camera mode changed");
          Keyboard.write('c');
          delay(delayBetweenPressess);
        }

        // 3x4 matrix keypad for toggling action groups
        int keypadKey = keypad.getKey();
        if (keypadKey) {
          for (int i = 1; i <= 9; i++) {
            if ((keypadKey == i)) {
              Serial.println("Action group " + String(i) + " activated");
              Keyboard.write(i);
              delay(delayBetweenPressess);
            }
          }
          if ((keypadKey == '1')) {
            Serial.println("Action group 1 activated");
            Keyboard.write('1');
            delay(delayBetweenPressess);
          }
          if ((keypadKey == '2')) {
            Serial.println("Action group 2 activated");
            Keyboard.write('2');
            delay(delayBetweenPressess);
          }
          if ((keypadKey == '3')) {
            Serial.println("Action group 3 activated");
            Keyboard.write('3');
            delay(delayBetweenPressess);
          }
          if ((keypadKey == '4')) {
            Serial.println("Action group 4 activated");
            Keyboard.write('4');
            delay(delayBetweenPressess);
          }
          if ((keypadKey == '5')) {
            Serial.println("Action group 5 activated");
            Keyboard.write('5');
            delay(delayBetweenPressess);
          }
          if ((keypadKey == '6')) {
            Serial.println("Action group 6 activated");
            Keyboard.write('6');
            delay(delayBetweenPressess);
          }
          if ((keypadKey == '7')) {
            Serial.println("Action group 7 activated");
            Keyboard.write('7');
            delay(delayBetweenPressess);
          }
          if ((keypadKey == '8')) {
            Serial.println("Action group 8 activated");
            Keyboard.write('8');
            delay(delayBetweenPressess);
          }
          if ((keypadKey == '9')) {
            Serial.println("Action group 9 activated");
            Keyboard.write('9');
            delay(delayBetweenPressess);
          }
          if ((keypadKey == '#')) {
            Serial.println("Throttle increased");
            Keyboard.write(KEY_LEFT_SHIFT);
            delay(delayBetweenPressess);
          }
          if ((keypadKey == '*')) {
            Serial.println("Throttle decreased");
            Keyboard.write(KEY_LEFT_CTRL);
            delay(delayBetweenPressess);
          }
          if ((keypadKey == '0')) {
            Serial.println("Cut throttle");
            Keyboard.write('x');
            delay(delayBetweenPressess);
          }
        }
        delay(25);
      }
      Keyboard.releaseAll();
      Keyboard.end();
      Serial.println("Keyboard emulation stopped");
    }
    update_gauges();
    delay(200);
  }
}

