#include "lcd.h"

SSD1306 display(0x3c, 21, 22);

void lcd_setup() {
    display.init();
    
    display.flipScreenVertically();
    display.setFont(ArialMT_Plain_10);
}

void lcd_home() {
    display.clear();

    lcd_menu_bar("MENU", "SEND");

    display.setTextAlignment(TEXT_ALIGN_CENTER);
    display.drawString(64, 20, "LoRaWAN Tester");

    display.display();
}

void lcd_about() {
    display.clear();

    lcd_menu_bar("", "OK");

    display.display();
}

void lcd_menu() {
    display.clear();

    lcd_menu_bar("NEXT", "CHANGE");

    //display.display();
}

void lcd_update() {
    display.display();
}

void lcd_menu_bar(const char* a, const char* b) {
    display.drawHorizontalLine(0, 52, 128);
    //display.drawVerticalLine(64, 54, 10);
    
    display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.drawString(0, 52, a);

    display.setTextAlignment(TEXT_ALIGN_RIGHT);
    display.drawString(127, 52, b);
}

void lcd_menu_item(unsigned int pos, const char * label, const char * value, bool selected) {

    Serial.print(pos);
    Serial.println("label");

    display.setTextAlignment(TEXT_ALIGN_LEFT);

    if (selected) {
        display.drawString(0, pos * 12, ">");    
    }

    display.drawString(12, pos * 12, label);

    display.setTextAlignment(TEXT_ALIGN_RIGHT);
    display.drawString(127, pos * 12, value);

}

void lcd_sleep() {
    display.clear();

    display.setTextAlignment(TEXT_ALIGN_CENTER_BOTH);
    display.drawString(64, 32, "I am going to sleep, bye!");

    display.display();
}

void lcd_txs() {
    display.clear();
    
    display.setTextAlignment(TEXT_ALIGN_CENTER);
    display.drawString(64, 0, "Sending...");
    
    lcd_menu_bar("STORNO", "");

    display.display();
}