#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_MOSI   9//9
#define OLED_CLK   10
#define OLED_DC    13//11
#define OLED_CS    12
#define OLED_RESET 11//13
//d0=10,d1=9,res=11,dc=13,cs=12
#define trigPinleft 42
#define echoPinleft 44
#define trigPinfront 50
#define echoPinfront 52
#define trigPinright 38
#define echoPinright 40
#define trigPinback 46
#define echoPinback 48
#define geelledlinks A10
#define geelledrechts A11
#define roodledvoor A8
#define roodledachter A9
#define groenled A12
#define noodstop 2
#define tuimel A5
#define party A7
#define tofrechtsonder 19
#define tofrechtsboven 16
#define toflinksboven 17
#define toflinksonder 18

#define motorrechtsdirection 6
#define motorlinksdirection 4
#define motorrechtsstep 3
#define motorlinksstep 5
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT,
                         OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);
long durationleft;
long durationfront;
long durationright;
long durationback;
int distanceleft;
int distancefront;
int distanceright;
int distanceback;
int i = 0;
void setup() {
  // put your setup code here, to run once:
  pinMode(trigPinleft, OUTPUT);
  pinMode(echoPinleft, INPUT);
  pinMode(trigPinfront, OUTPUT);
  pinMode(echoPinfront, INPUT);
  pinMode(trigPinright, OUTPUT);
  pinMode(echoPinright, INPUT);
  pinMode(trigPinback, OUTPUT);
  pinMode(echoPinback, INPUT);
  pinMode(geelledlinks, OUTPUT);
  pinMode(geelledrechts, OUTPUT);
  pinMode(roodledvoor, OUTPUT);
  pinMode(roodledachter, OUTPUT);
  pinMode(groenled, OUTPUT);
  pinMode(noodstop, INPUT_PULLUP);
  pinMode(tuimel, INPUT_PULLUP);
  pinMode(party, INPUT_PULLUP);
  pinMode(toflinksonder, OUTPUT);
  pinMode(toflinksboven, OUTPUT);
  pinMode(tofrechtsonder, OUTPUT);
  pinMode(tofrechtsboven, OUTPUT);
  pinMode(motorrechtsdirection, OUTPUT);
  pinMode(motorrechtsstep, OUTPUT);
  pinMode(motorlinksdirection, OUTPUT);
  pinMode(motorlinksstep, OUTPUT);
  display.begin(SSD1306_SWITCHCAPVCC);
  display.clearDisplay();
  display.display();
  display.setTextSize(3);  //Select the size of the text
  display.setTextColor(WHITE);  //for monochrome display only whit is possible
  display.setCursor(64, 30); //0,0 is the top left corner of the OLED screen
  display.print(10); //Write the variable to be displayed
  display.display();
  attachInterrupt(noodstop, noodstopmode, LOW);
}

void loop() {
  i = 1;
  // put your main code here, to run repeatedly:
  switch (i) {
    case 0: //initialiseren

    case 1: //autonome mode
      digitalWrite(motorrechtsdirection, HIGH);
      digitalWrite(motorlinksdirection, HIGH);
      for (int x = 0; x < 200; x++) {
        digitalWrite(motorrechtsstep, HIGH);
        digitalWrite( motorlinksstep, HIGH);
        delayMicroseconds(1000);
        digitalWrite(motorrechtsstep, LOW);
        digitalWrite(motorlinksstep, LOW);
        delayMicroseconds(1000);
      }

      digitalWrite(motorrechtsdirection, HIGH);
      digitalWrite(motorlinksdirection, LOW);
      for (int x = 0; x < 98; x++) {
        digitalWrite(motorrechtsstep, HIGH);
        digitalWrite( motorlinksstep, HIGH);
        delayMicroseconds(1000);
        digitalWrite(motorrechtsstep, LOW);
        digitalWrite(motorlinksstep, LOW);
        delayMicroseconds(1000);
      }
    case 2: //volgmode

    case 3: //sturen

    case 4: //stilstaan

    case 5: //totale reset
      reset();
  }

}

void reset() {

}

void noodstopmode() {
  digitalWrite(1, LOW);
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  while (1) {

  }
}
