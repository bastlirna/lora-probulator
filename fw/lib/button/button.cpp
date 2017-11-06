#include <button.h>

Button::Button(byte pin) {
    bounce.attach(pin);
    bounce.interval(5);
}

void Button::loop() {

    if (bounce.update()) {

        if (bounce.rose()) {
            lastEventTime = millis();
            _processing = true;
            return;
        }

        if (bounce.fell() && _processing && _state == Idle) {
            _state = ShortPress;
        }
    }

    if (_processing && _state == Idle) {
        if (millis() - lastEventTime > 500) {
            _state = LongPress;
        }
    }
}

ButtonState Button::state() {
    return _state;
}

void Button::reset() {
    _state = Idle;
    _processing = false;
}