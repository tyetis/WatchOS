class TimeSetScreen : public Screen {
  public:
    void (*fnUpdatedTime)(short hour, short minute) = 0;
    TimeSetScreen(String name, Adafruit_ST7789 *tft, void (*_fnUpdatedTime)(short hour, short minute), WatchOS* obj, void(WatchOS::*fnExit)()): Screen(name, tft, obj, fnExit) {
      fnUpdatedTime = _fnUpdatedTime;
    }
    void Show() {
      mode = false;
      TFT->setTextColor(ST77XX_WHITE, ST77XX_BLACK);
      TFT->setCursor(0, 0);
      TFT->println("Time Set");
      TFT->setTextSize(6);
      Update();
    };
    void Update() {
      TFT->setCursor(0, 50);
      if (mode == false)
        TFT->setTextColor(ST77XX_RED, ST77XX_WHITE);
      else
        TFT->setTextColor(ST77XX_WHITE, ST77XX_BLACK);
      TFT->print(PrettyTimePart(hour));
      if (mode == true)
        TFT->setTextColor(ST77XX_RED, ST77XX_WHITE);
      else
        TFT->setTextColor(ST77XX_WHITE, ST77XX_BLACK);
      TFT->print(":");
      TFT->print(PrettyTimePart(minute));
    }
    void Up() {
      if (mode == false) hour++;
      else if (mode == true) minute++;
      if (hour > 23) hour == 0;
      if (minute > 59) minute == 0;
      Update();
    }
    void Down() {
      if (mode == false) hour--;
      else if (mode == true) minute--;
      if (hour < 0) hour = 23;
      if (minute < 0) minute = 59;
      Update();
    }
    void Select() {
      if (mode == false) {
        mode = true;
        Update();
      }
      else {
        fnUpdatedTime(hour, minute);
        Exit();
      }
    }
  private:
    bool mode = false;
    int hour = 12;
    int minute = 37;
    String PrettyTimePart(short value) {
      return (value < 10 ? "0" : "") + String(value, DEC);
    }
};
