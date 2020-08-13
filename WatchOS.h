#include <WString.h>
#include "Screens.h"
#include "TimeSetScreen.h"
#include "MainScreen.h"
#include "NumberSetScreen.h"
#include "Menu.h"

class WatchOS {
  public:
    Adafruit_ST7789 *TFT;
    Menu *mainMenu = new Menu("Main Menu");
    Menu *settingsMenu = new Menu("Settings");
    Menu *applicationsMenu = new Menu("Apps");
    Screen *timesetscreen;
    Screen *numbersetscreen;
    Screen *mainscreen;
    Menu *activeMenu;
    Menu *previousMenu;
    Screen *activeScreen;
    int ActiveIndex = 0;
    short CustomValue = 0;
    void (*fnUpdatedTime)() = 0;
    void (*fnCustomValueUpdated)(short) = 0;
    WatchOS(Adafruit_ST7789 *tft) {
      TFT = tft;
    }
    void Init() {
      timesetscreen = new TimeSetScreen("Clock Set", TFT, fnUpdatedTime, this, &WatchOS::Back);
      numbersetscreen = new NumberSetScreen("Custom Set", TFT, CustomValue, fnCustomValueUpdated, this, &WatchOS::Back);
      mainscreen = new MainScreen("Lang Set", TFT, this, &WatchOS::Back);

      activeMenu = mainMenu;

      settingsMenu->AddItem(new Menu::MenuItem("saat ayrlr", 2, NULL, timesetscreen));
      settingsMenu->AddItem(new Menu::MenuItem("dil ayrlr", 2, NULL, mainscreen));
      settingsMenu->AddItem(new Menu::MenuItem("sistem ayrlr", 2, NULL, numbersetscreen));

      mainMenu->AddItem(new Menu::MenuItem("ayarlar", 1, settingsMenu, NULL));
      mainMenu->AddItem(new Menu::MenuItem("uyglamalar", 1, applicationsMenu, NULL));
      mainMenu->AddItem(new Menu::MenuItem("mesajlar", 0, NULL, NULL));

      applicationsMenu->AddItem(new Menu::MenuItem("calculator", 0, NULL, NULL));

      Update();
    }
    void Update() {
      if (activeScreen != NULL)
        activeScreen->Show();
      else {
        TFT->setTextColor(ST77XX_RED, ST77XX_BLACK);
        TFT->setCursor(0, 0);
        TFT->setTextSize(4);
        TFT->println(activeMenu->Name);
        TFT->setTextColor(ST77XX_WHITE, ST77XX_BLACK);

        for (byte i = 0; i < activeMenu->ItemCount; i++) {
          if (ActiveIndex == i) TFT->setTextColor(ST77XX_BLACK, ST77XX_YELLOW);
          else TFT->setTextColor(ST77XX_WHITE, ST77XX_BLACK);
          TFT->println(activeMenu->Items[i]->Name);
        }
      }
    }
    void Up() {
      if (activeScreen != NULL)
        activeScreen->Up();
      else {
        ActiveIndex++;
        if (ActiveIndex >= activeMenu->ItemCount) ActiveIndex = 0;
        Update();
      }
    }
    void Down() {
      if (activeScreen != NULL)
        activeScreen->Down();
      else {
        ActiveIndex--;
        if (ActiveIndex < 0) ActiveIndex = activeMenu->ItemCount - 1;
        Update();
      }
    }

    void Back() {
      activeMenu = previousMenu ? previousMenu : mainMenu;
      activeScreen = NULL;
      previousMenu = NULL;
      TFT->fillScreen(ST77XX_BLACK);
      Update();
    }
    void Select() {
      if (activeScreen != NULL)
        activeScreen->Select();
      else {
        TFT->fillScreen(ST77XX_BLACK);
        previousMenu = activeMenu;
        if (activeMenu->Items[ActiveIndex]->Type == 1) {
          activeMenu = activeMenu->Items[ActiveIndex]->menu;
          ActiveIndex = 0;
          Update();
        } else if (activeMenu->Items[ActiveIndex]->Type == 2) {
          activeScreen = activeMenu->Items[ActiveIndex]->screen;
          activeScreen->Show();
        }
      }
    }
};
