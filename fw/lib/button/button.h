#ifndef _button_h_
#define _button_h_

#include <Arduino.h>
#include <Bounce2.h>

enum ButtonState {
    Idle = 0, 
    ShortPress = 1, 
    LongPress = 2
};

class Button
{
 public:
    // Create an instance of the bounce library
    Button(byte pin);

    void loop();

    ButtonState state();
    void reset();

 protected:
    unsigned long lastEventTime;
    ButtonState _state = Idle;
    bool _processing = false;
    Bounce bounce = Bounce();

};

#endif
