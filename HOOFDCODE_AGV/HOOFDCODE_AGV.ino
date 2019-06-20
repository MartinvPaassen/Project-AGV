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
#define trigPinboom 19
#define echoPinboom 16
#define trigPinhek 17
#define echoPinhek 18
#define geelledlinks A10
#define geelledrechts A11
#define roodledvoor A8
#define roodledachter A9
#define groenled A12
#define noodstop 2
#define tuimel A5
#define party A7
/*#define tofrechtsonder 19
  #define tofrechtsboven 16
  #define toflinksboven 17
  #define toflinksonder 18*/
#define bocht 105
#define motorrechtsdirection 6
#define motorlinksdirection 4
#define motorrechtsstep 5
#define motorlinksstep 3
#define buzzer 8
#define boomafstand 10
#define minhek 13
#define maxhek 14
#define persoonafstand 7
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT,
                         OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

unsigned long timing;
unsigned long compensatie;
unsigned long current;
long durationleft;
long durationfront;
long durationright;
long durationback;
long durationboom;
long durationhek;
int distanceleft;
int distancefront;
int distanceright;
int distanceback;
int aantalbomen = 0;
int distanceboom;
int distancehek;
int voortgang = 0;
int flag = 0;
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
  pinMode(trigPinboom, OUTPUT);
  pinMode(echoPinboom, INPUT);
  pinMode(trigPinhek, OUTPUT);
  pinMode(echoPinhek, INPUT);
  pinMode(geelledlinks, OUTPUT);
  pinMode(geelledrechts, OUTPUT);
  pinMode(roodledvoor, OUTPUT);
  pinMode(roodledachter, OUTPUT);
  pinMode(groenled, OUTPUT);
  pinMode(noodstop, INPUT_PULLUP);
  pinMode(tuimel, INPUT_PULLUP);
  pinMode(party, INPUT_PULLUP);
  /*  pinMode(toflinksonder, OUTPUT);
    pinMode(toflinksboven, OUTPUT);
    pinMode(tofrechtsonder, OUTPUT);
    pinMode(tofrechtsboven, OUTPUT);*/
  pinMode(motorrechtsdirection, OUTPUT);
  pinMode(motorrechtsstep, OUTPUT);
  pinMode(motorlinksdirection, OUTPUT);
  pinMode(motorlinksstep, OUTPUT);
  pinMode(buzzer, OUTPUT);
  display.begin(SSD1306_SWITCHCAPVCC);
  display.clearDisplay();
  display.display();
  display.setTextSize(3);  //Select the size of the text
  display.setTextColor(WHITE);  //for monochrome display only whit is possible
  display.setCursor(64, 30); //0,0 is the top left corner of the OLED screen
  display.print(aantalbomen); //Write the variable to be displayed
  display.display();
  digitalWrite(groenled, HIGH);
  voortgang = 0;
}

void loop() {
  /*Serial.println("case");
    Serial.println(voortgang);
    Serial.println("case");
    Serial.println("voortgang");
    ultrasoonpersoon();
    Serial.println("iets");
    Serial.println("einde ");*/
  bomen();
  hek();
  ultrasoonpersoon();
  /* Serial.println("case");
    Serial.println(voortgang);
    Serial.println("distanceright");
    Serial.println(distanceright);
    Serial.println(distancefront);
    Serial.println(distanceleft);
    Serial.println(distanceback); */
  Serial.println("case");
  Serial.println(voortgang);
  if (digitalRead(noodstop) == LOW) {
    noodstopmode();
  }
  
  else if (distancefront <= persoonafstand or distanceleft <= persoonafstand or distanceback <= persoonafstand or distanceright <= persoonafstand) {
    voortgang = 4;
  }
  else if (digitalRead(tuimel) == LOW) {
    voortgang = 2;
  }
/*  else if (distancehek < minhek) {
    bijsturen(0);
  }
  else if (distancehek > maxhek) {
    bijsturen(1);
  }*/
  //else if (1) {
  //hallo
  //}
  else {
    voortgang = 1;
  }

  switch (voortgang) {
    case 0: //initialiseren
      Serial.println("initialisatie done");
      break;
    case 1: //autonome mode
      digitalWrite(roodledvoor, LOW);
      digitalWrite(roodledachter, LOW);
      if (1) {
        rechtdoor(0);
      }
      else {
        rechtdoor(1);
      }
      voortgang = 1; /*
      if (distancehek <= minhek) {
        bijsturen(0);
      }
      else if (distancehek >= maxhek) {
        bijsturen(1);
      }*/
      break;
    case 2: //volgmode
      volgen();
      voortgang = 2;

      break;
    case 3: //sturen
    /* if(){
        sturen(1);
      }
      else{
        sturen(0);
        }
        break;*/
    case 4: //stilstaan
      stilstaan();
      voortgang = 4;
      break;
    case 5: //totale reset
      reset();
      voortgang = 5;
      break;
  }

}
void stilstaan() {
  digitalWrite(roodledvoor, HIGH);
  digitalWrite(roodledachter, HIGH);
  digitalWrite(motorrechtsstep, LOW);
  digitalWrite(motorlinksstep, LOW);

}
void bijsturen(int i) {
  Serial.println("bijsturen");
  Serial.println(i);
  int a = 0;
  if (digitalRead(noodstop) == LOW) {
    noodstopmode();
  }
  if (i == 1) { //links
    digitalWrite(motorrechtsdirection, HIGH);
    digitalWrite(motorlinksdirection, LOW);
  }
  else { //rechts
    digitalWrite(motorrechtsdirection, LOW);
    digitalWrite(motorlinksdirection, HIGH);
  }
  digitalWrite(motorrechtsstep, HIGH);
  digitalWrite(motorlinksstep, HIGH);
  timing = micros();
  current = timing;
  while (a <= 3) {
    while (timing - current <= 1000) {
      timing = micros();
    }
    digitalWrite(motorrechtsstep, LOW);
    digitalWrite(motorlinksstep, LOW);
    a++;
  }
}

void doorrijden() {
  if (digitalRead(noodstop) == LOW) {
    noodstopmode();
  }
  timing = micros();
  current = timing;


}
void reset() {

}

void bomen() {
  if (digitalRead(noodstop) == LOW) {
    noodstopmode();
  }
  Serial.println("bomen tellen");
  // Serial.println(aantalbomen);
  timing = micros();
  current = timing;
  digitalWrite(trigPinboom, LOW);
  while ((timing - current) == 2) {
    timing = micros();
  }
  timing = micros();
  current = timing;
  digitalWrite(trigPinboom, HIGH);
  while ((timing - current) == 10) {
    timing = micros();
  }
  digitalWrite(trigPinboom, LOW);
  durationboom = pulseIn(echoPinboom, HIGH);
  distanceboom = durationboom * 0.017;
  // Serial.println(distanceboom);
  // digitalWrite(echoPinboom, LOW);
  /* timing = micros();
    current = timing;
    while (timing - current == 10) {
     timing = micros();
    }*/
  if (distanceboom < boomafstand or flag == 1) {
    flag = 1;
    //  Serial.println("flag gezet");
    if (distanceboom > boomafstand) {
      aantalbomen++;
      //Serial.println(aantalbomen);
      flag = 0;
      display.clearDisplay();
      display.display();
      display.setTextSize(3);  //Select the size of the text
      display.setTextColor(WHITE);  //for monochrome display only whit is possible
      display.setCursor(64, 30); //0,0 is the top left corner of the OLED screen
      display.print(aantalbomen); //Write the variable to be displayed
      display.display();
    }
  }
}

void hek() {
  Serial.println("hek");
  if (digitalRead(noodstop) == LOW) {
    noodstopmode();
  }
  timing = micros();
  current = timing;
  digitalWrite(trigPinhek, HIGH);
  while (timing - current == 10) {
    timing = micros();
  }
  digitalWrite(trigPinhek, LOW);
  durationhek = pulseIn(echoPinhek, HIGH);
  distancehek = durationhek * 0.017;
  // digitalWrite(echoPinhek, LOW);
}
void volgen() {

}

/*long durationleft;
  long durationfront;
  long durationright;
  long durationback;
  unsigned long timing;
  unsigned long current;
  int distanceleft;
  int distancefront;
  int distanceright;
  int distanceback;
*/
void ultrasoonpersoon() {
  Serial.println("ultrasoonpersoon");
  if (digitalRead(noodstop) == LOW) {
    noodstopmode();
  }
  //Serial.println("hall9o");
  digitalWrite(trigPinleft, LOW);
  timing = micros();
  current = timing;
  while (timing - current <= 2) {
    timing = micros();
  }
  digitalWrite(trigPinleft, HIGH);
  timing = micros();
  current = timing;
  while (timing - current <= 10) {
    timing = micros();
  }
  digitalWrite(trigPinleft, LOW);
  durationleft = pulseIn(echoPinleft, HIGH);
  //Serial.println("hallo11");
  distanceleft = durationleft * 0.017;
  //  digitalWrite(echoPinleft, LOW);
  //Serial.println("ultralinks");
  digitalWrite(trigPinfront, LOW);
  timing = micros();
  current = timing;
  while (timing - current <= 2) {
    timing = micros();
  }
  digitalWrite(trigPinfront, HIGH);
  timing = micros();
  current = timing;
  while (timing - current <= 10) {
    timing = micros();
  }
  //Serial.println("hallo");
  digitalWrite(trigPinfront, LOW);
  durationfront = pulseIn(echoPinfront, HIGH);
  distancefront = durationfront * 0.017;
  // digitalWrite(echoPinfront, LOW);
  digitalWrite(trigPinright, LOW);
  timing = micros();
  current = timing;
  while (timing - current <= 2) {
    timing = micros();
  }
  digitalWrite(trigPinright, HIGH);
  timing = micros();
  current = timing;
  while (timing - current <= 10) {
    timing = micros();
  }
  digitalWrite(trigPinright, LOW);
  durationright = pulseIn(echoPinright, HIGH);
  distanceright = durationright * 0.017;
  //digitalWrite(echoPinright, LOW);
  digitalWrite(trigPinback, LOW);
  timing = micros();
  current = timing;
  while (timing - current <= 2) {
    timing = micros();
  }
  digitalWrite(trigPinback, HIGH);
  timing = micros();
  current = timing;
  while (timing - current <= 10) {
    timing = micros();
  }
  digitalWrite(trigPinback, LOW);
  durationback = pulseIn(echoPinback, HIGH);
  distanceback = durationback * 0.017;
  // digitalWrite(echoPinback, LOW);
}


void rechtdoor(int richting) {
  int i = 0;
  int x = 0;
  int a = 0;
  int a1 = 0;
  int b = 0;
  int b1 = 0;
  Serial.println("rechtdoor");
  if (digitalRead(noodstop) == LOW) {
    noodstopmode();
  }
  if (richting == 1) {
    digitalWrite(motorrechtsdirection, HIGH);
    digitalWrite(motorlinksdirection, LOW);
  }
  else {
    digitalWrite(motorrechtsdirection, LOW);
    digitalWrite(motorlinksdirection, HIGH);
  }/*
  timing = micros();
  current = timing;
  while (x != 10) {
    if (digitalRead(noodstop) == LOW) {
      noodstopmode();
    }
    timing = micros();
    if (timing - current == 1500 and a1 == 0) {
      digitalWrite(motorrechtsstep, HIGH);
      digitalWrite(motorlinksstep, HIGH);
      a1 = 1;
      b1 = 1;
    }
    if (timing - current >= 3000 and b1 == 1) {
      digitalWrite(motorrechtsstep, LOW);
      digitalWrite(motorlinksstep, LOW);
      x++;
      current = timing;
      b1 = 0;
      a1 = 0;
    }
  }*/
  timing = micros();
  current = timing;
  while (i != 50) {
    if (digitalRead(noodstop) == LOW) {
      noodstopmode();
    }
    timing = micros();
    digitalWrite(motorrechtsstep, HIGH);
    digitalWrite(motorlinksstep, HIGH);
    if (timing - current >= 2000 and a == 0) {
      b = 1;
      a = 1;
      digitalWrite(motorrechtsstep, LOW);
      digitalWrite(motorlinksstep, LOW);
    }
    timing = micros();

    if (timing - current >= 4000 and b == 1) {
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
  Serial.println("sturen");
  if (digitalRead(noodstop) == LOW) {
    noodstopmode();
  }
  timing = micros();
  current = timing;
  // Serial.println("fase 1");
  // Serial.println(timing);
  // Serial.println(i);
  if (kant == 1) {
    digitalWrite(motorrechtsdirection, HIGH);
    digitalWrite(motorlinksdirection, HIGH);
    digitalWrite(geelledlinks, HIGH);
    digitalWrite(geelledrechts, LOW);
  }
  else {
    digitalWrite(motorrechtsdirection, LOW);
    digitalWrite(motorlinksdirection, LOW);
    digitalWrite(geelledrechts, HIGH);
    digitalWrite(geelledlinks, LOW);
  }
  digitalWrite(motorrechtsstep, HIGH);
  digitalWrite(motorlinksstep, HIGH);
  while (i <= bocht) {
    if (timing - current >= 4000 and a == 0) {
      //Serial.println("fase 2");
      //Serial.println(timing);
      b = 1;
      a = 1;
      digitalWrite(motorrechtsstep, LOW);
      digitalWrite(motorlinksstep, LOW);
    }
    timing = micros();
    if (timing - current >= 8000 and b == 1) {
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
  Serial.println("noodstop");
  timing = micros();
  current = timing;
  int a = 0;
  int b = 0;
  compensatie = timing;
  digitalWrite(motorrechtsstep, LOW);
  digitalWrite(motorlinksstep, LOW);
  digitalWrite(motorrechtsdirection, LOW);
  digitalWrite(motorlinksdirection, LOW);
  digitalWrite(groenled, LOW);

  while (digitalRead(noodstop) == LOW) {
    timing = micros();
    if (timing - current >= 1000) {
      if (b == 0) {
        digitalWrite(buzzer, HIGH);
        b = 1;
        current = timing;
      }

      else {
        current = timing;
        digitalWrite(buzzer, LOW);
        current = timing;
        b = 0;
      }
    }
    if (timing - compensatie >= 500000) {
      if (a == 0) {
        Serial.println("aan");
        digitalWrite(roodledvoor, HIGH);
        digitalWrite(roodledachter, HIGH);
        digitalWrite(geelledlinks, HIGH);
        digitalWrite(geelledrechts, HIGH);
        compensatie = timing;
        a = 1;
      }

      else {
        Serial.println("uit");
        digitalWrite(roodledvoor, LOW);
        digitalWrite(roodledachter, LOW);
        digitalWrite(geelledlinks, LOW);
        digitalWrite(geelledrechts, LOW);
        compensatie = timing;
        a = 0;
      }
    }
  }
  voortgang = 0;

}
