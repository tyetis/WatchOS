#include <Keypad.h>
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <SPI.h>
#include <Wire.h>
#include "DS1307.h"
#include "WatchOS.h"

const byte satir = 2;
const byte sutun = 3;
long timethreadmillis = 0;
char keys[satir][sutun] = {
  {'1', '2', '3'},
  {'4', '5', '6'}
};
byte satirPin[satir] = { 2, 10 };
byte sutunPin[sutun] = { 5, 6, 7 };
Keypad keypad = Keypad( makeKeymap(keys), satirPin, sutunPin, satir, sutun);
#define TFT_CS        -1
#define TFT_RST        9 // Or set to -1 and connect to Arduino RESET pin
#define TFT_DC         8
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);
DS1307 clock;//define a object of DS1307 class

WatchOS watchOS = WatchOS(&tft);

void setup() {
  Serial.begin(9600);
  clock.begin();
  clock.fillByYMD(2013, 1, 19); //Jan 19,2013
  /*clock.fillByHMS(15, 28, 30); //15:28 30"
    clock.fillDayOfWeek(SAT);//Saturday
    clock.setTime();//write time to the RTC chip*/
  tft.init(240, 240, SPI_MODE2);

  tft.fillScreen(ST77XX_BLACK);
  tft.setCursor(0, 0);

  watchOS.fnUpdatedTime = UpdateTime;
  watchOS.CustomValue = 123;
  watchOS.fnCustomValueUpdated = CustomValueUpdated;
  watchOS.Init();
}

void loop() {
  keypadEvent();
}

void UpdateTime(short hour, short minute) {
  Serial.println("UpdatedTime Triggered " + String(hour) + " " + String(minute));
}
void CustomValueUpdated(short value) {
  Serial.println("CustomValueUpdated Triggered " + String(value));
}
void ShowTime() {
  if (millis() - timethreadmillis > 1000) {
    timethreadmillis = millis();
    clock.getTime();
    String timee = PrettyTimePart(clock.hour) + ":" + PrettyTimePart(clock.minute) + ":" + PrettyTimePart(clock.second);
    tft.setTextColor(ST77XX_WHITE, ST77XX_BLACK);
    tft.setCursor(0, 0);
    tft.setTextSize(5);
    tft.println(timee);
    Serial.println(timee);
  }
}

String PrettyTimePart(uint8_t value) {
  return (value < 10 ? "0" : "") + String(value, DEC);
}
void keypadEvent() {
  char key = keypad.getKey();
  if (key == '1')
    watchOS.Up();
  else if (key == '2')
    watchOS.Down();
  else if (key == '3')
    watchOS.Select();
  else if (key == '4')
    watchOS.Back();
}
