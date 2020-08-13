## Graphical Interface For AVR Based C++

This library serves to create simple menus and screens for AVR based chips. The library has been tested and run on the Atmega328p and ST7789 LCD screen. 
Adafruit_GFX and Adafruit_ST7789 are used as display drivers, but the driver library can be changed with minor changes.
Arduino framework and object oriented programming standards were used in the project.

**WatchOS**
```cpp
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);
WatchOS watchOS = WatchOS(&tft);

void setup() {
  tft.init(240, 240, SPI_MODE2);
  tft.fillScreen(ST77XX_BLACK);
  tft.setCursor(0, 0);

  watchOS.Init();
}
```

**Inputs**
```cpp
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
```

![Image 1](https://i.ibb.co/X7YXkzL/IMG-20200813-160922.jpg)
![Image 1](https://i.ibb.co/CP3d4n6/IMG-20200813-160948.jpg)
