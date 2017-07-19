# Meteor-Defenders
### Game for OLED 128*64 display for Arduino from Adafruit.

This meteor defenders game uses only the basic geometrical shapes from the Adafruit GFX library. You will see your spaceship, with this you will have to defend the earth from meteors. If a meteor hits the earth the game resets.
The only thing you need besides the code and the display, are four push buttons.

### Display

To connect the display, I changed my address to 0x3C, you can change yours at line 112. The common address for 128x64 is 0x3D.
The display can be connected to the arduino via I2C. The sda and scl should go to the arduino sda and scl pins, or to pin A4 (sda) and pin A5 (scl). The vcc goes to the 5V pin and gnd to gnd obviously. (Your display might use 3.3V, I don't know how to use it in that case but you will probably have to use some converters if you want to use it with a 5V arduino.)

### Controls

The pushbuttons will have to be connected to pins:

1. UP to A3
2. DOWN to A0
3. RIGHT to A1
4. LEFT to A2 (The left control is not yet used is this game.)

I didn't use the build-in arduino step-down resistors but you can change the code to do that ofcourse.

### Bluetooth

To use the BT version of the game you can use this app: "Bluetooth RC Controller". It was originally made to control cars with but it seems to work fine for spaceships too. Up and down do the same thing and so does the right button (which fires). To connect the app to the Arduino you can use a simple HC-06 BT modem. The only pins you need are the RX and TX pins which have to connect to TX and RX of the arduino (so they flip).
In the app there are a couple different modes you can use, the code only works if you use the app in the "Send When Change" mode. (To connect with the Arduino you just select the correct modem from the list. If it asks for a password - which in my case it did't - try "0000", "1234" or just try no password at all.) 


### I'm trying to add:

1. A permanently savable highscore. (By storing it in the PROGMEM.)
2. A laser you can shoot with.
3. A way to make it harder.
4. A way to store the game on an SD-card.
