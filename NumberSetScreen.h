class NumberSetScreen : public Screen {
  private:
    String name;
    short value;
  public:
    void (*fnCustomValueUpdated)(short) = 0;
    NumberSetScreen(String _name, Adafruit_ST7789 *tft, short _value, void (*_fnCustomValueUpdated)(short), WatchOS* obj, void(WatchOS::*fnExit)()): Screen(name, tft, obj, fnExit) {
      fnCustomValueUpdated = _fnCustomValueUpdated;
      name = _name;
      value = _value;
    }
    void Show() {
      TFT->setTextColor(ST77XX_WHITE, ST77XX_BLACK);
      TFT->setCursor(0, 0);
      TFT->println(name);
      TFT->setTextSize(6);
      Update();
    };
    void Update() {
      TFT->setCursor(0, 50);
      TFT->print(value);
    }
    void Up() {
      value++;
      Update();
    }
    void Down() {
      value--;
      Update();
    }
    void Select() {
      fnCustomValueUpdated(value);
      Exit();
    }
};
