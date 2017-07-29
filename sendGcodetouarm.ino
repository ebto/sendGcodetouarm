/*
   Esplora Sends Gcode to uArm (Swift Pro via Serial Monitor)

   This sketch uses Esplora's keyboard emulation to control
   uArm Swfit Pro (4 DOF robot arm) via serial monitor.

   When one of the 4 Esplora buttons (not joystick) on the right
   is pressed, Esplora sends keybaord message in G-Gode -
   move-to command to 1 of 4 predefined coordinate.

   Step 1: Compile this sketch to Esplora Keep it connected to PC but
   don't touch the buttons yet. If you have TFT LCD it displays which
   button is pressed.

   Step 2: Connect uArm Swift(Pro) to PC, power on.

   Step 3: From Arduino IDE, connect port to uArm (like /dev/cu.usbmodem!a13441)
   and select board as Mega 2560.

   Step 4: Open serial terminal from Arduino IDE.
   Check baud rate = 115200 and "Newline" is selected. uArm will
   echo text in terminal and is ready to receive commands

   Step 5: Put cursor in serial terminal input box and press a button on Esplora.
   A string like #25 G0 X180 Y-180 Z75 F10000

   Step 6: It moves! (Careful to push button only when cursor is in serial
   terminal input box, else you get gcode all over the place.

   Caution: closing serial terminal will make uArm go limp and lose all motor
   tension. Hold the uArm or put a cushion around to protect the effector.

   Created: 26 July 2017
   Updated: 30 July 2017
   Author: Eric Ong (ebto on GitHub)
   Credits: sketch is based on sample provided on Arduino IDE - EsploraKart,
   written by Enrico Gueli. Original comments are left as-is,

*/

#include <SoftwareSerial.h>
#include <Esplora.h>
#include <Keyboard.h>
#include <TFT.h>
#include <SPI.h>

const String vSpeed = " F10000\n";
const String vPrefix = "#25 G0 ";

boolean buttonStates[4];

const byte buttons[] = {
  SWITCH_RIGHT,     // 4
  SWITCH_LEFT,      // 2
  SWITCH_UP,        // 3
  SWITCH_DOWN       // 1
};

void setup() {

  // Open serial communications
  Serial.begin(115200);

  // initialize TFT LCD display
  EsploraTFT.begin();

  // clear the screen with a black background
  EsploraTFT.background(ST7735_BLACK);

  DisplaySplash(); // display sketch name

  // set the font size for the loop
  EsploraTFT.setTextSize(2);

  // set the font color
  EsploraTFT.stroke(ST7735_GREEN);
  EsploraTFT.text("Button:", 0, 0);

  //  Serial.println("Move to default resting position");
  //  Serial.println("#25 G0 X100.15 Y-7.39 Z100.57 F10000");

}

void loop() {
  // Iterate through all the buttons:
  for (byte thisButton = 0; thisButton < 4; thisButton++) {

    boolean lastState = buttonStates[thisButton];
    boolean newState = Esplora.readButton(buttons[thisButton]);

    if (lastState != newState) { // Something changed!
      /*
        The Keyboard library allows you to "press" and "release" the
        keys as two distinct actions. These actions can be
        linked to the buttons we're handling.
      */
      if (newState == PRESSED) {

        EsploraTFT.stroke(ST7735_GREEN);

        if (buttons[thisButton] == SWITCH_DOWN) {
          //Serial.print("Down\t");
          Keyboard.print(vPrefix + "X150 Y0 Z75" + vSpeed);
          EsploraTFT.text("Down", 100, 0);
          delay(240);
          EsploraTFT.stroke(ST7735_BLACK);
          EsploraTFT.text("Down", 100, 0);
        } else if (buttons[thisButton] == SWITCH_LEFT) {
          //Serial.print("Left\t");
          Keyboard.print(vPrefix + "X180 Y180 Z75" + vSpeed);
          EsploraTFT.text("Left", 100, 0);
          delay(240);
          EsploraTFT.stroke(ST7735_BLACK);
          EsploraTFT.text("Left", 100, 0);
        } else if (buttons[thisButton] == SWITCH_UP) {
          //Serial.print("Up\t");
          Keyboard.print(vPrefix + "X250 Y0 Z150" + vSpeed);
          EsploraTFT.text("Up", 100, 0);
          delay(240);
          EsploraTFT.stroke(ST7735_BLACK);
          EsploraTFT.text("Up", 100, 0);
        } else if (buttons[thisButton] == SWITCH_RIGHT) {
          //Serial.print("Right\t");
          Keyboard.println(vPrefix + "X180 Y-180 Z75" + vSpeed);
          EsploraTFT.text("Right", 100, 0);
          delay(240);
          EsploraTFT.stroke(ST7735_BLACK);
          EsploraTFT.text("Right", 100, 0);
        } else {
          //EsploraTFT.text("Idle", 100, 0);
          delay(240);
          EsploraTFT.stroke(ST7735_BLACK);
          EsploraTFT.text("Idle", 100, 0);
        }
      } // if newstate == PRESSED end

      // Store the new button state, so you can sense a difference later:
      buttonStates[thisButton] = newState;

    } // if laststate != newstate
  } // for..loop end
}  // void loop end

void DisplaySplash() {   // display first screen
  EsploraTFT.stroke(ST7735_WHITE);
  EsploraTFT.setTextSize(2);
  EsploraTFT.text("ESPLORA", 0, 0);
  EsploraTFT.text("SWITCH BTNS", 0, 20);
  EsploraTFT.text("SEND GCODE", 0, 40);
  EsploraTFT.text("Show button", 0, 80);
  EsploraTFT.text("pressed", 0, 100);
  delay(3000);
  EsploraTFT.background(ST7735_BLACK);
}
