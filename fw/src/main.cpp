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

void setup() {
    Serial.begin(115200);

    delay(10);

    log_setup();
    hal_setup();
    lcd_setup();
    core_setup();
    lora_setup();

    screenMgr.change(&home);

    Log.trace("Setup done!");
}

unsigned long screenMirrorTime;

void loop() {

    hal_loop();
    lora_loop();

    runtime.loop();
    screenMgr.loop();

    if (btnOff.update() && btnOff.rose()) {

        Log.trace("Sleep request detected");

        if (runtime.periodic) {
            runtime.periodicStop();
        }

        lcd_sleep();

        delay(1500);

        if (btnOff.update() && btnOff.fell()) {
            // cancel sleep routine
            return;
        }

        Log.trace("Going to sleep");

        //esp_sleep_enable_ext0_wakeup(GPIO_NUM_33,1); //1 = High, 0 = Low
        esp_deep_sleep_enable_ext0_wakeup(GPIO_NUM_36, 0);

        display.displayOff();
        lora_off();
        esp_deep_sleep_start();

        // this will newer called
        while(1);
    }

    if (settings.screenMirror) {
        if (millis() - screenMirrorTime > 500) {
            screenMirrorTime = millis();
            display.sendBufferOnSerial();
        }
    }
}
