#ifndef _aboutcreen_h_
#define _aboutcreen_h_

#include <screen.h>

class AboutScreen : public Screen {

public:
    void enter();
    void leave();
    void loop();

    void onBPress();
};

#endif