#include "home.h"

#include "hal.h"
#include "lcd.h"
#include "core.h"

void MsgScreen::enter() {
    

    display.clear();

    display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.drawStringMaxWidth(0, 0, 128, message);

    lcd_menu_bar("", "OK");

    display.display();
}

void MsgScreen::leave() {
}

void MsgScreen::loop() {
}

void MsgScreen::onBPress() {
    screenMgr.change(&home);
}