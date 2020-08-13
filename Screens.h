#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789

class WatchOS;
class Screen {
  public:
    String Name;
    Adafruit_ST7789 *TFT;
    void(WatchOS::*fnExit)();
    WatchOS* obj;
    Screen(String name, Adafruit_ST7789 *tft, WatchOS* _obj, void(WatchOS::*_fnExit)()) {
      Name = name;
      TFT = tft;
      fnExit = _fnExit;
      obj = _obj;
    }
    virtual void Show() = 0;
    virtual void Update() = 0;
    virtual void Up() = 0;
    virtual void Down() = 0;
    virtual void Select() = 0;
    void Exit() {
      (obj->*fnExit)();
    }
};
