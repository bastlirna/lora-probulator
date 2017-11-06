#include <Arduino.h>

#include <core.h>

#include <hal.h>
#include <lcd.h>
#include <lora.h>

#include <screen/home.h>
#include <screen/menu.h>
#include <screen/tx.h>
#include <screen/rx.h>

#include "Esp.h"
#include "esp_deep_sleep.h"
#include "esp_attr.h"

#define BUTTON_PIN_BITMASK 0x200000000 // 2^33 in hex

//RTC_DATA_ATTR int bootCount = 0;

HomeScreen home = HomeScreen();
MenuScreen menu = MenuScreen();
AboutScreen about = AboutScreen();
TxScreen txs = TxScreen();
RxScreen rxs = RxScreen();
MsgScreen msg = MsgScreen();

ScreenMgr screenMgr = ScreenMgr();


RTC_DATA_ATTR bool confirm = false;


void setup() {
    Serial.begin(115200);

    delay(100);

    //++bootCount;
    //Serial.println("Boot number: " + String(bootCount));
  
    hal_setup();
    lcd_setup();
    lora_setup();

    screenMgr.change(&home);

    Serial.println("Setup done!");
}

void loop() {

    hal_loop();
    lora_loop();

    screenMgr.loop();

    //delay(50);

    if (btnOff.update() && btnOff.rose()) {

        Serial.println("Turn Off");

        lcd_sleep();

        delay(1500);

        //esp_sleep_enable_ext0_wakeup(GPIO_NUM_33,1); //1 = High, 0 = Low
        esp_deep_sleep_enable_ext0_wakeup(GPIO_NUM_36, 0);
        
        //Go to sleep now
        display.displayOff();
        lora_off();
        
        esp_deep_sleep_start();

        Serial.println("Zzz...");
    }

}