#ifndef _rxscreen_h_
#define _rxscreen_h_

#include <screen.h>

class RxScreen : public Screen {

public:
    void enter();
    void leave();
    void loop();

    void onAPress();
    void onBPress();

    bool autoClose;
};


#endif 