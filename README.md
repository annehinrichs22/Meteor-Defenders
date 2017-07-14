# Meteor-Defenders
### Game for OLED 128*64 for Arduino from Adafruit.

This meteor defenders game uses only the basic geometrical shapes from the Adafruit GFX library.
The only thing you need besides the code and the display, are four push buttons. The connections can be found in the code.
To connect the display, I changed my address to 0x3C, you can change yours at line 112. The common address for 128x64 is 0x3D.

You will have to stay alive as long as you can.

The game uses 4 pushbuttons.

I'm trying to add:

1. A permanently savable highscore.
2. A laser you can shoot with.
3. A way to make it harder.
