#ifndef _homescreen_h_
#define _homescreen_h_

#include <screen.h>

class HomeScreen : public Screen {

public:
    void enter();
    void leave();
    void loop();

    virtual void onAPress();
    virtual void onBPress();
};


#endif