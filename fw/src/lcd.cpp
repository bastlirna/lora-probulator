#include "lcd.h"

#include "lora.h"
#include "core.h"

#include "imgs/icons.h"

#define ICON(name) name##_width, name##_height, name##_bits 

SSD1306 display(0x3c, 21, 22);



void lcd_setup() {
    display.init();
    
    display.flipScreenVertically();
    display.setFont(ArialMT_Plain_10);
}

void lcd_home() {
    display.clear();

    const char * action;

    if (runtime.periodic) {
        if (runtime.periodicRunning) {
            action = "STOP";
        } else {
            action = "START";
        }
    } else {
        action = "SEND";
    }

    lcd_menu_bar("MENU", action);

    // device 
    display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.drawString(0, 0, lora_dev_name(settings.currentDev));

    byte next_icon = 118;

    // confirm
    if (settings.confirm) {
        display.drawXbm(next_icon, 1, ICON(ack));
        next_icon -= 11;
    }

    // up/down icon
    if (settings.donwlink) {
        display.drawXbm(next_icon, 1, ICON(downlink));
    } else {
        display.drawXbm(next_icon, 1, ICON(uplink));
    }
    
    // interval
    if (runtime.periodic) {
        display.setTextAlignment(TEXT_ALIGN_CENTER);    
        display.drawString(0, 64, String(INTERVALS[settings.interval]) + "s");
    }

    display.drawHorizontalLine(0, 12, 128);

    if (runtime.periodic) {

        const int top = 37;            
        const int len = 92;

        if (runtime.periodicRunning) {

            display.setTextAlignment(TEXT_ALIGN_RIGHT);
            display.drawString(126, top - 1, String(round(runtime.countdownTime()/1000) + 1) + " s");

            display.drawRect(2, top + 2, len, 7);
            display.fillRect(4, top + 4, round((len - 3) * runtime.countdownTime() / runtime.interval), 3);

        } else {
            display.setTextAlignment(TEXT_ALIGN_CENTER);
            display.drawString(64, top - 1, "Ready");
        }

        if (settings.confirm) {

            if (runtime.counter == 0) {
                display.setTextAlignment(TEXT_ALIGN_LEFT);
                display.drawString(1, 19, "Stats:");
                
                display.setTextAlignment(TEXT_ALIGN_RIGHT);
                display.drawString(126, 19, "-");
            } else {
                display.setTextAlignment(TEXT_ALIGN_LEFT);
                display.drawString(1, 19, "Stats:");
            
                display.setTextAlignment(TEXT_ALIGN_RIGHT);
                display.drawString(126, 19, String(runtime.successCounter) + "/" + String(runtime.counter) + " (" + String(runtime.successRate) + " %)");
            }

        } else {
            display.setTextAlignment(TEXT_ALIGN_LEFT);
            display.drawString(1, 19, "Counter:");
            
            display.setTextAlignment(TEXT_ALIGN_RIGHT);
            display.drawString(126, 19, String(runtime.counter));
        }
        
    } else {

        display.setTextAlignment(TEXT_ALIGN_CENTER_BOTH);
        display.drawString(64, 32, "Ready");
    }
     
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

void lcd_menu_item(unsigned int pos, const char * label, String value, bool selected) {

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