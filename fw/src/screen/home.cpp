#include "home.h"

#include "hal.h"
#include "lcd.h"
#include "core.h"

void HomeScreen::enter() {
    lcd_home();
}

void HomeScreen::leave() {
}

void HomeScreen::loop() {
    lcd_home();
 
    if (runtime.periodicRunning && runtime.send) {
        screenMgr.change(&txs);
    }
}

void HomeScreen::onAPress() {

    if (runtime.periodic) {
        runtime.periodicStop();
    }

    screenMgr.change(&menu);
}

void HomeScreen::onBPress() {

    if (runtime.periodic) {
        if (runtime.periodicRunning) {
            runtime.periodicStop();
        } else {
            runtime.periodicStart();
        }
    } else {
        screenMgr.change(&txs);
    }

}

void HomeScreen::onBLongPress() {
    if (runtime.periodic) {
        runtime.periodicStop();
        runtime.periodicReset();
    }
}