# sendGcodetouarm
Arduino Esplora sends fixed GCode to uArm Swift via serial terminal

This sketch uses Esplora's keyboard emulation to control uArm Swfit Pro (4 DOF robot arm) via serial monitor. 

When one of the 4 Esplora buttons (not joystick) on the right is pressed, Esplora sends keyboard message in G-Gode move-to command to 4 predefined coordinates.

Step 1: Compile this sketch to Esplora. Keep it connected to PC but don't touch Esplora buttons yet. If you have TFT LCD it will display which button is pressed.

Step 2: Connect uArm Swift(Pro) to PC, power on.

Step 3: From Arduino IDE, switch connected port to uArm (like /dev/cu.usbmodem!a13441 on Mac OS) and select Mega 2560 as board.

Step 4: Open serial terminal. Check baud rate = 115200 and "Newline" is selected. uArm will echo text in terminal and is ready to receive commands.

Step 5: Put cursor in serial terminal input box and press a button on Esplora. A string like #25 G0 X180 Y-180 Z75 F10000 is sent.

Step 6: It moves! (Careful to push button only when cursor is in serial terminal input box, else you get gcode all over the place.

Caution: closing serial terminal will make uArm go limp and lose all motor tension. Hold the uArm or put a cushion around to protect the effector.
