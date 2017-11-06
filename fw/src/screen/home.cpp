#include "home.h"

#include "hal.h"
#include "lcd.h"
#include "core.h"

void HomeScreen::enter() {
    Serial.println("ENTER home");

    lcd_home();
}

void HomeScreen::leave() {
    Serial.println("LEAVE home");
}

void HomeScreen::loop() {
}

void HomeScreen::onAPress() {
    screenMgr.change(&menu);
}

void HomeScreen::onBPress() {
    screenMgr.change(&txs);
}