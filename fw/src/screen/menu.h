#ifndef _menuscreen_h_
#define _menuscreen_h_

#include <screen.h>

struct MenuItem {
    virtual const char * label();
    virtual const char * value();
    virtual void change();
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

private:
    void update();

    MenuItem* items[10];
    int len;
    int current=0;

};

#endif