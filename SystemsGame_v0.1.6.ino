#include <FastLED.h>
#include <Arduino.h>
#include <U8g2lib.h>
#include <SPI.h>
#include <Wire.h>

#define NUM_LEDS 20
#define DATA_PIN 11
#define SCORE_PIN 12
#define SCORE_LEDS 10
#define BRIGHTNESS  95

CRGB leds[NUM_LEDS];
CRGB sleds[NUM_LEDS];
U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0); 

bool reachedEnd = false;
byte gameState = 0;
//byte ledSpeed = 0;
int period = 1000;
unsigned long time_now = 0;
byte Position = 0;
byte level = 0;
int speakerPin = 8;
byte previousgameState = 0;
const byte ledSpeed[5] = {50, 40, 35, 20, 10};
bool secondchanced = false;






//Debounce
bool findRandom = false;
byte spot = 0;
 
void setup() {
  // put your setup code here, to run once:
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.addLeds<WS2812B, SCORE_PIN, GRB>(sleds, SCORE_LEDS);
  FastLED.setBrightness(BRIGHTNESS );
  u8g2.begin();
  pinMode(4, INPUT_PULLUP);
  Serial.begin(9600);
  Serial.println("Reset");
}
 
void loop() {
  // put your main code here, to run repeatedly:
  if (gameState == 0) {
    fill_rainbow(leds, NUM_LEDS, 0, 7); //2 = longer gradient strip
    fill_rainbow(sleds, SCORE_LEDS, 0, 7); //2 = longer gradient strip

    u8g2.clearBuffer();          // clear the internal memory
    u8g2.setFont(u8g2_font_logisoso28_tr);  // choose a suitable font at https://github.com/olikraus/u8g2/wiki/fntlistall
    u8g2.drawStr(31,29,"PLAY?");  // write something to the internal memory
    u8g2.sendBuffer();         // transfer internal memory to the display
   
    if (digitalRead(4) == LOW) {
      Position = 0;
      findRandom = true;
      u8g2.clearBuffer();         // clear the internal memory
      u8g2.sendBuffer();         // transfer internal memory to the display
      delay(500);
      for (byte i = 0; i < NUM_LEDS; i++) {
        leds[i].setRGB(0, 0, 0);
        delay(40);
        FastLED.show();
      }
      for (byte i = 0; i < SCORE_LEDS; i++) {
        sleds[i].setRGB(0, 0, 0);
        FastLED.show();
      }
      gameState = 1;
    }
    FastLED.show();
  }
  if (gameState == 1) {
    previousgameState = gameState;
    

    u8g2.clearBuffer();         // clear the internal memory
    u8g2.setFont(u8g2_font_logisoso28_tr);  // choose a suitable font at https://github.com/olikraus/u8g2/wiki/fntlistall
    u8g2.drawStr(4,29,"Level 1");  // write something to the internal memory
    u8g2.sendBuffer();         // transfer internal memory to the display
    period = ledSpeed[1];
    if (millis() > time_now + period) {
      time_now = millis();
      if (findRandom) {
        spot = random(16) + 2;
        findRandom = false;
      }
      leds[spot - 2].setRGB(255, 190, 0);
      leds[spot - 1].setRGB(255, 190, 0);
      leds[spot].setRGB(0, 255, 0);
      leds[spot + 1].setRGB(255, 190, 0);
      leds[spot + 2].setRGB(255, 190, 0);
      sleds[0].setRGB(0, 255, 0);
      PlayGame(spot - 1, spot + 1);
    }
    if (digitalRead(4) == LOW) {
      delay(300);
      findRandom = false;
      if (Position > spot - 2 && Position < spot + 4) {
        level = gameState;
        gameState = 98;
      } else {
        gameState = 99;
      }
    }
  }
  if (gameState == 2) {
//    period = 320;
    previousgameState = gameState;
    u8g2.clearBuffer();         // clear the internal memory
    u8g2.setFont(u8g2_font_logisoso28_tr);  // choose a suitable font at https://github.com/olikraus/u8g2/wiki/fntlistall
    u8g2.drawStr(4,29,"Level 2");  // write something to the internal memory
    u8g2.sendBuffer();         // transfer internal memory to the display
    period = ledSpeed[2];
    if (millis() > time_now + period) {
      time_now = millis();
      if (findRandom) {
        spot = random(16) + 2;
        findRandom = false;
      }
      leds[spot - 2].setRGB(255, 190, 0);
      leds[spot - 1].setRGB(255, 190, 0);
      leds[spot].setRGB(0, 255, 0);
      leds[spot + 1].setRGB(255, 190, 0);
      leds[spot + 2].setRGB(255, 190, 0);
      sleds[1].setRGB(0, 255, 0);
      PlayGame(spot - 1, spot + 1);
    }
    if (digitalRead(4) == LOW) {
      delay(300);
      if (Position > spot - 2 && Position < spot + 4) {
        level = gameState;
        gameState = 98;
      } else {
        gameState = 99;
      }
    }
  }
  if (gameState == 3) {
    previousgameState = gameState;
    u8g2.clearBuffer();         // clear the internal memory
    u8g2.setFont(u8g2_font_logisoso28_tr);  // choose a suitable font at https://github.com/olikraus/u8g2/wiki/fntlistall
    u8g2.drawStr(4,29,"Level 3");  // write something to the internal memory
    u8g2.sendBuffer();         // transfer internal memory to the display
    period = ledSpeed[2];
    if (millis() > time_now + period) {
      time_now = millis();
      if (findRandom) {
        spot = random(16) + 3;
        findRandom = false;
      }
      leds[spot - 1].setRGB(255, 140, 0);
      leds[spot].setRGB(0, 255, 0);
      leds[spot + 1].setRGB(255, 140, 0);
      sleds[2].setRGB(0, 255, 0);
      PlayGame(spot - 1, spot + 1);
    }
    if (digitalRead(4) == LOW) {
      delay(300);
      findRandom = false;
      if (Position > spot - 1 && Position < spot + 3) {
        level = gameState;
        gameState = 98;
      } else {
        gameState = 99;
      }
    }
  }
  if (gameState == 4) {
    previousgameState = gameState;
    u8g2.clearBuffer();         // clear the internal memory
    u8g2.setFont(u8g2_font_logisoso28_tr);  // choose a suitable font at https://github.com/olikraus/u8g2/wiki/fntlistall
    u8g2.drawStr(4,29,"Level 4");  // write something to the internal memory
    u8g2.sendBuffer();         // transfer internal memory to the display
    period = ledSpeed[3];
    if (millis() > time_now + period) {
      time_now = millis();
      if (findRandom) {
        spot = random(16) + 3;
        findRandom = false;
      }
      leds[spot - 1].setRGB(255, 140, 0);
      leds[spot].setRGB(0, 255, 0);
      leds[spot + 1].setRGB(255, 140, 0);
      sleds[3].setRGB(0, 255, 0);
      PlayGame(spot - 1, spot + 1);
    }
    if (digitalRead(4) == LOW) {
      delay(300);
      findRandom = false;
      if (Position > spot - 1 && Position < spot + 3) {
        level = gameState;
        gameState = 98;
      } else {
        gameState = 99;
      }
    }
  }
  if (gameState == 5) {
    previousgameState = gameState;
    u8g2.clearBuffer();         // clear the internal memory
    u8g2.setFont(u8g2_font_logisoso28_tr);  // choose a suitable font at https://github.com/olikraus/u8g2/wiki/fntlistall
    u8g2.drawStr(4,29,"Level 5");  // write something to the internal memory
    u8g2.sendBuffer();         // transfer internal memory to the display
    period = ledSpeed[2];
    if (millis() > time_now + period) {
      time_now = millis();
      if (findRandom) {
        spot = random(16) + 3;
        findRandom = false;
      }
      leds[spot].setRGB(0, 255, 0);
      sleds[4].setRGB(0, 255, 0);
      PlayGame(spot, spot);
    }
    if (digitalRead(4) == LOW) {
      delay(300);
      if (Position == spot+1) {
        level = gameState;
        gameState = 98;
      } else {
        gameState = 99;
      }
    }
  }
  if (gameState == 6) {
    previousgameState = gameState;
    u8g2.clearBuffer();         // clear the internal memory
    u8g2.setFont(u8g2_font_logisoso28_tr);  // choose a suitable font at https://github.com/olikraus/u8g2/wiki/fntlistall
    u8g2.drawStr(4,29,"Level 6");  // write something to the internal memory
    u8g2.sendBuffer();         // transfer internal memory to the display
    period = ledSpeed[3];
    if (millis() > time_now + period) {
      time_now = millis();
      if (findRandom) {
        spot = random(16) + 3;
        findRandom = false;
      }
      leds[spot].setRGB(0, 255, 0);
      sleds[5].setRGB(0, 255, 0);
      PlayGame(spot, spot);
    }
    if (digitalRead(4) == LOW) {
      delay(300);
      if (Position == spot+1) {
        level = gameState;
        gameState = 98;
      } else {
        gameState = 99;
      }
    }
  }
  if (gameState == 7) {
    previousgameState = gameState;
    u8g2.clearBuffer();         // clear the internal memory
    u8g2.setFont(u8g2_font_logisoso28_tr);  // choose a suitable font at https://github.com/olikraus/u8g2/wiki/fntlistall
    u8g2.drawStr(4,29,"Level 7");  // write something to the internal memory
    u8g2.sendBuffer();         // transfer internal memory to the display
    period = ledSpeed[4];
    if (millis() > time_now + period) {
      time_now = millis();
      if (findRandom) {
        spot = random(16) + 3;
        findRandom = false;
      }
      leds[spot].setRGB(0, 255, 0);
      sleds[5].setRGB(0, 255, 0);
      PlayGame(spot, spot);
    }
    if (digitalRead(4) == LOW) {
      delay(300);
      if (Position == spot+1) {
        level = gameState;
        gameState = 98;
      } else {
        gameState = 99;
      }
    }
  }
  if (gameState == 98) {
    winner();
  }
  if (gameState == 99) {
    
    // generate pseudo float in the range of 0 to 100
    float randNumber = random(100);

    // probability of 40%
    if (randNumber >= 59 && secondchanced == false)
    {
      secondchance();
    }

    else
    {
      loser();
    }
  }
}

void PlayGame(byte bound1, byte bound2) {
  leds[Position].setRGB(255, 0, 0);
  if (Position < bound1 + 1 || Position > bound2 + 1) {
    leds[Position - 1].setRGB(0, 0, 0);
  }
  FastLED.show();
  Position++;
  if (Position >= NUM_LEDS) {
    leds[Position - 1].setRGB(0, 0, 0);
    Position = 0;
  }
}
 
void winner() {
  for (byte i = 0; i < 3; i++) {
    for (byte j = 0; j < NUM_LEDS; j++) {
      leds[j].setRGB(0, 255, 0);
    }
    FastLED.show();
    tone(speakerPin, 1000, 300);
    delay(500);
    clearLEDS();
    FastLED.show();
    delay(500);
  }
  findRandom = true;
  Position = 0;
 
  gameState = level + 1;
  if (gameState > 7) {
    gameState = 0;
  }
}
void loser() {
  for (byte i = 0; i < 3; i++) {
    for (byte j = 0; j < NUM_LEDS; j++) {
      leds[j].setRGB(255, 0, 0);
    }
    FastLED.show();
    tone(speakerPin, 250, 300);
    delay(500);
    clearLEDS();
    FastLED.show();
    delay(500);
  }

  // reset secondchance bool
  secondchanced = false;
  gameState = 0;

}

void secondchance() {
  u8g2.clearBuffer();          // clear the internal memory
  u8g2.setFont(u8g2_font_logisoso28_tr);  // choose a suitable font at https://github.com/olikraus/u8g2/wiki/fntlistall
  u8g2.drawStr(0,29,"re do");  // write something to the internal memory
  u8g2.sendBuffer();         // transfer internal memory to the display
  for (byte i = 0; i < 3; i++) {
    for (byte j = 0; j < NUM_LEDS; j++) {
      leds[j].setRGB(0, 0, 255);
    }
    FastLED.show();
    tone(speakerPin, 1000, 300);
    delay(500);
    clearLEDS();
    FastLED.show();
    delay(500);
  }
  findRandom = true;
  Position = 0;
 
  gameState = previousgameState;
  // set secondchance bool to true to stop second chance being applicable in future.
  secondchanced = true;
}

void clearLEDS() {
  for (byte i = 0; i < NUM_LEDS; i++) {
    leds[i].setRGB(0, 0, 0);
  }
}
void winAll(){
  
}
