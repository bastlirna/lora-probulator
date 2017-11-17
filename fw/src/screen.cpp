#include <screen.h>
#include <Arduino.h>

#include "core.h"

#include "hal.h"

// --- Screen ---

void Screen::onAPress() {
}

void Screen::onALongPress() {
}

void Screen::onBPress() {
}

void Screen::onBLongPress() {
}

// --- Screen MGR ---

ScreenMgr::ScreenMgr() {
    _nextScreen = nullptr;
    changePanding = false;
}

void ScreenMgr::loop() {

    // enter
    if (changePanding) {

        _current = _nextScreen;
        changePanding = false;
        _current->enterTime = millis();
        _current->enter();
    }

    // events
    if (btnA.state() == ShortPress) {
        btnA.reset();
        _current->onAPress();
    }

    if (btnA.state() == LongPress) {
        btnA.reset();
        _current->onALongPress();
    }

    if (btnB.state() == ShortPress) {
        btnB.reset();
        _current->onBPress();
    }

    if (btnB.state() == LongPress) {
        btnB.reset();
        _current->onBLongPress();
    }

    // loop
    _current->loop();
   
    // leave
    if (changePanding) {
        _current->leave();
    }
}

void ScreenMgr::change(Screen* nextScreen) {

    _nextScreen = nextScreen;
    changePanding = true;

}