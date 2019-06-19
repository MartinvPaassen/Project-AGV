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
#define bocht 105
#define motorrechtsdirection 6
#define motorlinksdirection 4
#define motorrechtsstep 5
#define motorlinksstep 3
#define buzzer 99
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT,
                         OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);
long durationleft;
long durationfront;
long durationright;
long durationback;
unsigned long timing;
unsigned long current;
int distanceleft;
int distancefront;
int distanceright;
int distanceback;
int i = 0;
void noodstopmode();
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

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
  pinMode(buzzer, OUTPUT);
  /* display.begin(SSD1306_SWITCHCAPVCC);
    display.clearDisplay();
    display.display();
    display.setTextSize(3);  //Select the size of the text
    display.setTextColor(WHITE);  //for monochrome display only whit is possible
    display.setCursor(64, 30); //0,0 is the top left corner of the OLED screen
    display.print(10); //Write the variable to be displayed
    display.display();
  */
  attachInterrupt(noodstop, noodstopmode, LOW);
}

void loop() {
  i = 1;
  // put your main code here, to run repeatedly:
  switch (i) {
    case 0: //initialiseren

    case 1: //autonome mode

    case 2: //volgmode

    case 3: //sturen

    case 4: //stilstaan

    case 5: //totale reset
      reset();
  }

}
trigPinleft 42
#define echoPinleft 44
#define trigPinfront 50
#define echoPinfront 52
#define trigPinright 38
#define echoPinright 40
#define trigPinback 46
#define echoPinback 48
void reset() {

}

void bomen() {

}
void volgen() {

}

long durationleft;
long durationfront;
long durationright;
long durationback;
unsigned long timing;
unsigned long current;
int distanceleft;
int distancefront;
int distanceright;
int distanceback;

void ultrasoonpersoon() {

  digitalWrite(echoPinleft, LOW);
  digitalWrite(trigPinleft, HIGH);
  //tijd
  digitalWrite(trigPin
  duratonleft=pulseIn(echoPinleft,HIGH);
  digitalWrite(trigPinfront);
  digitalWrite(echoPinfront);

  digitalWrite(trigPinright);
  digitalWrite(echoPinright);

  digitalWrite(trigPinback);
  digitalWrite(echoPinback);

  digitalWrite();
  digitalWrite();
}


void rechtdoor(int richting) {
  int i = 0;
  int a = 0;
  int b = 0;
  int current;
  if (richting == 1) {
    digitalWrite(motorrechtsdirection, HIGH);
    digitalWrite(motorlinksdirection, LOW);
  }
  else {
    digitalWrite(motorrechtsdirection, LOW);
    digitalWrite(motorlinksdirection, HIGH);
  }
  timing = micros();
  current = timing;
  while (i != 1) {
    timing = micros();
    // Serial.println("fase 1");
    // Serial.println(timing);
    // Serial.println(i);
    digitalWrite(motorrechtsstep, HIGH);
    digitalWrite(motorlinksstep, HIGH);
    if (timing - current >= 3000 and a == 0) {
      //Serial.println("fase 2");
      //Serial.println(timing);
      b = 1;
      a = 1;
      digitalWrite(motorrechtsstep, LOW);
      digitalWrite(motorlinksstep, LOW);
    }
    timing = micros();
    if (timing - current >= 6000 and b == 1) {
      i++;
      b = 0;
      a = 0;
      //Serial.println("fase 3");
      // Serial.println(timing);
      current = timing;
    }
  }
}



void sturen(int kant) {
  int i = 0;
  int a = 0;
  int b = 0;
  int current;
  timing = micros();
  current = timing;
  // Serial.println("fase 1");
  // Serial.println(timing);
  // Serial.println(i);
  if (kant == 1) {
    digitalWrite(motorrechtsdirection, HIGH);
    digitalWrite(motorlinksdirection, HIGH);
  }
  else {
    digitalWrite(motorrechtsdirection, LOW);
    digitalWrite(motorlinksdirection, LOW);
  }
  digitalWrite(motorrechtsstep, HIGH);
  digitalWrite(motorlinksstep, HIGH);
  while (i <= bocht) {
    if (timing - current >= 3000 and a == 0) {
      //Serial.println("fase 2");
      //Serial.println(timing);
      b = 1;
      a = 1;
      digitalWrite(motorrechtsstep, LOW);
      digitalWrite(motorlinksstep, LOW);
    }
    timing = micros();
    if (timing - current >= 6000 and b == 1) {
      i++;
      b = 0;
      a = 0;
      //Serial.println("fase 3");
      // Serial.println(timing);
      current = timing;
    }
    // if (i == 105) {
    //   a = 3;
    //  b = 3;

  }
}






void iets() {
  digitalWrite(motorrechtsdirection, HIGH);
  digitalWrite(motorlinksdirection, HIGH);
  for (int x = 0; x < 200; x++) {
    digitalWrite(motorrechtsstep, HIGH);
    digitalWrite( motorlinksstep, HIGH);
    delayMicroseconds(2000);
    digitalWrite(motorrechtsstep, LOW);
    digitalWrite(motorlinksstep, LOW);
    delayMicroseconds(2000);
  }
  /*
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
  */
}
















void noodstopmode() {
  int tel = 0;
  digitalWrite(motorrechtsstep, LOW);
  digitalWrite(motorlinksstep, LOW);
  digitalWrite(motorrechtsdirection, LOW);
  digitalWrite(motorlinksdirection, LOW);
  while (digitalRead(noodstop) == LOW) {
    tel++;
    if (tel == 500) {
      digitalWrite(buzzer, HIGH);
    }
    if (tel == 1000) {
      tel = 0;
      digitalWrite(buzzer, LOW);
    }
  }
}
