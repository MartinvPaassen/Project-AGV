
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
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT,
                         OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);
//char i=5;
void setup() {
  // put your setup code here, to run once:
  //the variable to be displayed
  display.begin(SSD1306_SWITCHCAPVCC);
  display.clearDisplay();
  display.setTextSize(3);  //Select the size of the text
  display.setTextColor(WHITE);  //for monochrome display only whit is possible
  display.setCursor(64, 30); //0,0 is the top left corner of the OLED screen
  display.print(10); //Write the variable to be displayed
  display.display();
}

void loop() {
  // put your main code here, to run repeatedly:


}
