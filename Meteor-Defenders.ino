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

boolean quit = false;
char stepUD = 0;

char x1 = 8;
char y1 = 6;
char x2 = 8;
char y2 = 20;
char x3 = 23;
char y3 = 13;

char bulx = 0;
char buly = 0;
boolean bullet = false;

char meteox = 0;
char meteoy = 0;
boolean meteor = false;

char meteox2 = 0;
char meteoy2 = 0;
boolean meteor2 = false;

char meteorsize = 3;

char meteorspeed = 1;
char bulletspeed = 4;

int luck = 0;
char trispeed = 3;
unsigned int score = 0;
unsigned int highscore = 0;

char randx1 = 100;
char randx2 = 127;
char randy1 = 6;
char randy2 = 58;

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
  quit = false;
  stepUD = 0;

  x1 = 8;
  y1 = 6;
  x2 = 8;
  y2 = 20;
  x3 = 23;
  y3 = 13;

  bulx = 0;
  buly = 0;
  bullet = false;

  meteox = 0;
  meteoy = 0;
  meteor = false;

  meteox2 = 0;
  meteoy2 = 0;
  meteor2 = false;

  meteorsize = 3;

  bulletspeed = 4;
  meteorspeed = 1;

  luck = random(40, 100);
  trispeed = 3;
  // don't reset the score
  // don't reset the highscore

  randx1 = 100;
  randx2 = 127;
  randy1 = 6;
  randy2 = 58;

  //intro------------------------------------------------------------------------------
  
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


  while (digitalRead(BUTUP) == ! HIGH) {
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

 score  = 0;

// Part two --------------------The Game--------------

  while (quit == false) {

    //check if the triangle is bad
    if (y1 < 1) {
      y1 = 0;
      y2 = 14;
      y3 = 7;
    }

    if (y2 > 63) {
      y1 = 49;
      y2 = 63;
      y3 = 56;
    }

    //check inputs
    if (digitalRead(BUTDOWN) == HIGH) {
      stepUD = trispeed;
    }

    if (digitalRead(BUTUP) == HIGH) {
      stepUD = -trispeed;
    }

    if (digitalRead(BUTLEFT) == HIGH) {
      bullet = true;
    }

    //bullet maker
    if (bullet == true) {
      if (bulx < 127) {
        display.drawPixel(bulx, buly, WHITE);
        bulx = bulx + bulletspeed;
      }
      else {
        bullet = false;
      }
    }
    else {
      bulx = x3;
      buly = y3;
    }

    //meteor maker
    if (luck < 0) {

      meteor = true;
      if (score > 1000) {
        meteor2 = true;
      }
      if (score > 1500) {
        meteorspeed = 2;
      }
    }

    //meteor 1
    if (meteor == true) {


      if (meteox > 0) {
        display.drawCircle(meteox, meteoy, 3, WHITE);
        meteox = meteox - meteorspeed;
      }
      else {
        meteor = false;
        quit = true;
      }
      
      if ((bullet == true) && (bulx <= meteox + meteorsize) && (bulx >= meteox - meteorsize) && (buly <= meteoy + meteorsize) && (buly >= meteoy - meteorsize)) {
         meteor = false;
         bullet = false;
         luck = random(25, 125);
         display.drawLine(bulx - 6, buly - 6, bulx + 6, buly + 6, WHITE);
         display.drawLine(bulx - 6, buly + 6, bulx + 6, buly - 6, WHITE);
      }
      
    }
    else {

      meteox = random(randx1, randx2);
      meteoy = random(randy1, randy2);
    }

    // meteor 2
    if (meteor2 == true) {


      if (meteox2 > 0) {
        display.drawCircle(meteox2, meteoy2, 3, WHITE);
        meteox2 = meteox2 - meteorspeed;
      }
      else {
        meteor2 = false;
        quit = true;
      }

      if ((bullet == true) && (bulx <= meteox2 + meteorsize) && (bulx >= meteox2 - meteorsize) && (buly <= meteoy2 + meteorsize) && (buly >= meteoy2 - meteorsize)) {
         meteor2 = false;
         bullet = false;
         luck = random(25, 125);
         display.drawLine(bulx - 6, buly - 6, bulx + 6, buly + 6, WHITE);
         display.drawLine(bulx - 6, buly + 6, bulx + 6, buly - 6, WHITE);
    }
    
    }
    else {
      meteox2 = random(randx1, randx2);
      meteoy2 = random(randy1, randy2);
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
    if (luck > 0) {
      luck = luck - 5;
    }
    else {
      luck = -1;
    }
    score = score + 1;

    delay(10);
    display.clearDisplay();
  }
}
