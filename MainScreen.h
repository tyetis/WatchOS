class MainScreen : public Screen {
  public:
    MainScreen(String name, Adafruit_ST7789 *tft, WatchOS* obj, void(WatchOS::*fnExit)()): Screen(name, tft, obj, fnExit) {}
    void Show() {
      TFT->fillScreen(ST77XX_BLACK);
      TFT->setCursor(0, 0);
      TFT->println("MainPage");
    }
    void Up() {
    }
    void Update() {
    }
    void Down() {
    }
    void Select() {
      Exit();
    }
};