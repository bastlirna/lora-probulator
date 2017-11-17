#ifndef _menuscreen_h_
#define _menuscreen_h_

#include <screen.h>
#include <Arduino.h>

struct MenuItem {
    virtual const char * label();
    virtual String value();
    virtual void change();
    virtual void reset();
    virtual void apply();
};

class MenuScreen : public Screen {

public:

    MenuScreen();

    void enter();
    void leave();
    void loop();    

    virtual void onAPress();
    virtual void onALongPress();
    virtual void onBPress();
    virtual void onBLongPress();

private:
    void update();

    MenuItem* items[10];
    int len;
    int current = 0;
    bool itemChanged = false;

};

#endif