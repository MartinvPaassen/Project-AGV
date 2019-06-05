#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_MOSI   13//9
#define OLED_CLK   10
#define OLED_DC    11
#define OLED_CS    12
#define OLED_RESET 9//13
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
void setup() {
  // put your setup code here, to run once:
  //serial.begin(9600);
  pinMode(trigPinleft, OUTPUT);
  pinMode(echoPinleft, INPUT);
  pinMode(trigPinfront, OUTPUT);
  pinMode(echoPinfront, INPUT);
  pinMode(trigPinright, OUTPUT);
  pinMode(echoPinright, INPUT);
  pinMode(trigPinback, OUTPUT);
  pinMode(echoPinback, INPUT);
  pinMode(geelledlinks,OUTPUT);
  pinMode(geelledrechts,OUTPUT);
  pinMode(roodledvoor,OUTPUT);
  pinMode(roodledachter,OUTPUT);
  pinMode(groenled,OUTPUT);
  pinMode(13,OUTPUT);
 // display.begin(SSD1306_SWITCHCAPVCC);
 // display.clearDisplay();
 // display.display();
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(trigPinleft, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPinleft, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinleft, LOW);
  durationleft = pulseIn(echoPinleft, HIGH);
  distanceleft = durationleft * 0.017;
  //serial.println("links");
  //serial.println(distanceleft);
  digitalWrite(trigPinfront, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPinfront, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinfront, LOW);
  durationfront = pulseIn(echoPinfront, HIGH);
  distancefront = durationfront * 0.017;
    //serial.println("voor");
  //serial.println(distancefront);
  digitalWrite(trigPinright, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPinright, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinright, LOW);
  durationright = pulseIn(echoPinright, HIGH);
  distanceright = durationright * 0.017;
    //serial.println("rechts");
  //serial.println(distanceright);
  digitalWrite(trigPinback, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPinback, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinback, LOW);
  durationback = pulseIn(echoPinback, HIGH);
  distanceback = durationback * 0.017;
    //serial.println("achter");
  //serial.println(distanceback);
  if (distanceleft <= 5) {
    digitalWrite(geelledlinks, HIGH);
    digitalWrite(13,HIGH);
  }
  else {
    digitalWrite(13,LOW);
    digitalWrite(geelledlinks, LOW);
  }
    if (distanceright <= 5) {
      digitalWrite(geelledrechts, HIGH);
    }
    else {
      digitalWrite(geelledrechts, LOW);
    }
    if (distancefront <= 5) {
      digitalWrite(roodledvoor, HIGH);
    }
    else {
      digitalWrite(roodledvoor, LOW);
    }
    if (distanceback <= 5) {
      digitalWrite(roodledachter, HIGH);
    }
    else {
      digitalWrite(roodledachter, LOW);
    
  }
//  delay(500);
 // display.setTextSize(1);
 // display.setTextColor(WHITE);
 // display.setCursor(0, 0);
 // display.print(10);
 // display.display();
}
