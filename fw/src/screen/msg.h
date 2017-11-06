#ifndef _msgscreen_h_
#define _msgscreen_h_

#include <Arduino.h>

#include <screen.h>

class MsgScreen : public Screen {

public:
    void enter();
    void leave();
    void loop();

    void onBPress();

    String message;
};

#endif