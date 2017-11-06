#include "home.h"

#include "hal.h"
#include "lcd.h"
#include "core.h"

void AboutScreen::enter() {
    display.clear();
    lcd_menu_bar("", "OK");

    display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.drawString(0, 0, "LoRa Tester v0.1");

    display.display();
}

void AboutScreen::leave() {
}

void AboutScreen::loop() {

    display.setColor(BLACK);
    display.fillRect(0, 20, 128, 12);

    display.setColor(WHITE);
    display.drawString(0, 20, "Uptime: " + String(millis()));
    lcd_update();
}

void AboutScreen::onBPress() {
    screenMgr.change(&home);
}