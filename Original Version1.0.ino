// OLED Meteor Defenders using Adafruit GFX Library

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <avr/pgmspace.h>
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2


#define LOGO16_GLCD_HEIGHT 16
#define LOGO16_GLCD_WIDTH  16
static const unsigned char PROGMEM logo16_glcd_bmp[] =
{ B00000000, B11000000,
  B00000001, B11000000,
  B00000001, B11000000,
  B00000011, B11100000,
  B11110011, B11100000,
  B11111110, B11111000,
  B01111110, B11111111,
  B00110011, B10011111,
  B00011111, B11111100,
  B00001101, B01110000,
  B00011011, B10100000,
  B00111111, B11100000,
  B00111111, B11110000,
  B01111100, B11110000,
  B01110000, B01110000,
  B00000000, B00110000
};

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

#define BUTUP A3
#define BUTDOWN A0
#define BUTRIGHT A1
#define BUTLEFT A2

// Dont forget to change the values in the redefinition section too!

int quit = 0;
int stepUD = 0;

int x1 = 8;
int y1 = 6;
int x2 = 8;
int y2 = 20;
int x3 = 23;
int y3 = 13;

int bulx = 0;
int buly = 0;
int bullet = 0;
int bulletcounter = 0;

int meteox = 0;
int meteoy = 0;
int meteor = 0;

int meteox2 = 0;
int meteoy2 = 0;
int meteor2 = 0;

int luck = 50;
int trispeed = 3;
int score = 0;
int highscore = 0;

int randx1 = 100;
int randx2 = 128;
int randy1 = 6;
int randy2 = 58;

void setup()   {
  Serial.begin(9600);

  pinMode(BUTUP, INPUT);
  pinMode(BUTDOWN, INPUT);
  pinMode(BUTRIGHT, INPUT);
  pinMode(BUTLEFT, INPUT);

  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
  // init done

  // Show image buffer on the display hardware.
  // Since the buffer is intialized with an Adafruit splashscreen
  // internally, this will display the splashscreen.
  display.display();
  delay(2000);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("Build by A. Hinrichs (C)2017");
  display.display();
  delay(2000);
}

void loop()  {
  
  // Redefinition section
  quit = 0;
  stepUD = 0;

  x1 = 8;
  y1 = 6;
  x2 = 8;
  y2 = 20;
  x3 = 23;
  y3 = 13;

  bulx = 0;
  buly = 0;
  bullet = 0;
  bulletcounter = 0;

  meteox = 0;
  meteoy = 0;
  meteor = 0;

  meteox2 = 0;
  meteoy2 = 0;
  meteor2 = 0;

  luck = 50;
  trispeed = 3;
  // don't reset the score
  // don't reset the highscore

  randx1 = 100;
  randx2 = 128;
  randy1 = 6;
  randy2 = 58;
  
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(64 - (32 / 2), 32 - (8 / 2) - 10);
  display.println("METEOR!");
  display.setCursor(64 - (40 / 2), 32 - (8 / 2));
  display.println("DEFENDERS");
  display.display();
  delay(500);
  display.clearDisplay();
  quit = 0;
  luck = 50;
  Serial.println("q = 0");


  while (digitalRead(BUTUP) == ! HIGH) {
    Serial.println("hallo");
    // title
    display.setCursor(64 - (32 / 2), 32 - (8 / 2) - 10);
    display.println("METEOR!");
    display.setCursor(64 - (40 / 2), 32 - (8 / 2));
    display.println("DEFENDERS");
    display.setCursor(0, 0);
    // High score
    if (score > highscore) {
      highscore = score;
    }
    display.println("High score:");
    display.setCursor(20, 8);
    display.print(highscore);
    
    display.display();
    // turns the text on and off
    delay(200);
    display.setCursor(64 - (128 / 2), 32 - (8 / 2) + 10);
    display.println("Press UP long to continue");
    display.display();
    delay(200);
    display.clearDisplay();
  }

 // only reset the score here (for saving the highscore)
 score  = 0;

// Part two --------------------The Game--------------

  while (quit == 0) {
    Serial.println("deel twee");


    //check if the triangle is bad
    if ((y1 < 1) /*&& ((y2-14)<1) && ((y3-7)<1)*/) {
      y1 = 0;
      y2 = 14;
      y3 = 7;
    }

    if ((y2 > 63)/* && ((y2+14)<1) && ((y3+7)>63)*/) {
      y1 = 49;
      y2 = 63;
      y3 = 56;
    }

    //check inputs
    if (digitalRead(BUTDOWN) == HIGH) {

      stepUD = stepUD + trispeed;

    }

    if (digitalRead(BUTUP) == HIGH) {

      stepUD = stepUD - trispeed;

    }

    if (digitalRead(BUTLEFT) == HIGH) {

      bullet = 1;

    }

    //bullet maker
    if (bullet == 1) {
      if (bulx < 128) {
        display.drawPixel(bulx, buly, WHITE);
        bulx = bulx + 4;
      }
      else {
        bullet = 0;
      }
    }
    else {
      bulx = x3;
      buly = y3;
    }

    //meteor maker
    if (luck < 0) {

      meteor = 1;
      if (score > 1000) {
        meteor2 = 1;
      }
    }

    //meteor 1
    if (meteor == 1) {


      if (meteox > 0) {
        display.drawCircle(meteox, meteoy, 3, WHITE);
        meteox = meteox - 1;
      }
      else {
        meteor = 0;
        Serial.println("q = 1");
      }
    }
    else {

      meteox = random(randx1, randx2);
      meteoy = random(randy1, randy2);
    }

    if (meteox == 1) {
      quit = 1;
    }
    if ((bullet == 1) && ((bulx <= meteox + 4) && (bulx >= meteox - 4) && (buly <= meteoy + 4) && (buly >= meteoy - 4))) {
      meteor = 0;
      bullet = 0;
      luck = luck + 50;
      display.drawLine(bulx - 6, buly - 6, bulx + 6, buly + 6, WHITE);
      display.drawLine(bulx - 6, buly + 6, bulx + 6, buly - 6, WHITE);
    }

    // meteor 2
    if (meteor2 == 1) {


      if (meteox2 > 0) {
        display.drawCircle(meteox2, meteoy2, 3, WHITE);
        meteox2 = meteox2 - 1;
      }
      else {
        meteor2 = 0;
        Serial.println("q = 1");
      }
    }
    else {
      meteox2 = random(randx1, randx2);
      meteoy2 = random(randy1, randy2);
    }
    if (meteox2 == 1) {
      quit = 1;
    }

    if ((bullet == 1) && ((bulx <= meteox2 + 4) && (bulx >= meteox2 - 4) && (buly <= meteoy2 + 4) && (buly >= meteoy2 - 4))) {
      meteor2 = 0;
      bullet = 0;
      luck = luck + 50;
      display.drawLine(bulx - 6, buly - 6, bulx + 6, buly + 6, WHITE);
      display.drawLine(bulx - 6, buly + 6, bulx + 6, buly - 6, WHITE);
    }

    //standard stuff (Starring: Circle as the big plannet, Triangle as the space ship)
    display.fillCircle(-58, 32, 64, WHITE);
    display.setCursor(0, 0);
    display.print(score);
    display.drawTriangle(x1, y1, x2, y2, x3, y3, WHITE);
    display.display();

    //traingle controll variables
    y1 = y1 + stepUD;
    y3 = y3 + stepUD;
    y2 = y2 + stepUD;

    //counters
    stepUD = 0;
    luck = luck - 1;
    score = score + 1;

    delay(10);
    display.clearDisplay();
  }
}
