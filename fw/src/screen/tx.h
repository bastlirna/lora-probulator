#ifndef _txscreen_h_
#define _txscreen_h_

#include <screen.h>

class TxScreen : public Screen {

public:
    void enter();
    void leave();
    void loop();

    void onAPress();
};


#endif