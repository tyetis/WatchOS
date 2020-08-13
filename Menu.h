#include <WString.h>

class Menu {
  public:
    class MenuItem {
      public:
        Menu *menu;
        Screen *screen;
        byte Type;
        MenuItem(String sname, byte type, Menu *_menu, Screen *_screen) {
          Name = sname;
          menu = _menu;
          screen = _screen;
          Type = type;
        }
        String Name;
    };
    int ItemCount;
    MenuItem *Items[5];
    String Name;
    Menu(String sname) {
      Name = sname;
      ItemCount = 0;
    }
    void AddItem(MenuItem *item) {
      Items[ItemCount] = item;
      ItemCount++;
    }
};
