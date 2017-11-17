#ifndef _screen_h_
#define _screen_h_

class Screen {

public:
    Screen() {};
  
    virtual void loop();
    virtual void enter();
    virtual void leave();

    virtual void onAPress();
    virtual void onALongPress();
    virtual void onBPress();
    virtual void onBLongPress();

    unsigned long enterTime;
};

class ScreenMgr {

public:
    ScreenMgr();

    void loop();
    void change(Screen* nextScreen);

    mutable bool changePanding;

    Screen* _current;
    mutable Screen* _nextScreen;

protected:
    

};

#endif