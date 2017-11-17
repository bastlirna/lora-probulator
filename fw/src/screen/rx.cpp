#include "rx.h"

#include "hal.h"
#include "lcd.h"
#include "core.h"
#include <lmic.h>

void RxScreen::enter() {
    

    display.clear();

    display.setTextAlignment(TEXT_ALIGN_CENTER);

    if (settings.confirm) {
        display.drawString(64, 0, "DONE (with confirm)");
    } else {
        display.drawString(64, 0, "DONE");
    }

    if (LMIC.txrxFlags & TXRX_ACK) {

        runtime.incrementStats(true);

/*
        Serial.println(F("Received ack"));
        Serial.println();
        printf("RSSI: %d \n", LMIC.rssi);
        printf("SNR: %d \n", LMIC.snr);
        printf("Freq: %d \n", LMIC.freq);
        printf("TXpow: %d dBm\n", LMIC.txpow);
        printf("globalDutyRate: %d \n", LMIC.globalDutyRate);
        printf("globalDutyAvail: %d \n", LMIC.globalDutyAvail);
        printf("datarate: %d \n", LMIC.datarate);
        */
        ostime_t airtime = calcAirTime(LMIC.rps, LMIC.dataLen);
        //printf("Air time: %d.", airtime / 100);
        //printf("%d ms\n", airtime % 100);

        display.setTextAlignment(TEXT_ALIGN_LEFT);
        display.drawString(0, 14, "Rx RSSI");

        display.setTextAlignment(TEXT_ALIGN_RIGHT);
        display.drawString(59, 14, String(LMIC.rssi));

        display.setTextAlignment(TEXT_ALIGN_LEFT);
        display.drawString(0, 24, "Rx SNR");

        display.setTextAlignment(TEXT_ALIGN_RIGHT);
        display.drawString(59, 24, String(LMIC.snr));

        display.setTextAlignment(TEXT_ALIGN_LEFT);
        display.drawString(0, 34, "Rx Slot");

        display.setTextAlignment(TEXT_ALIGN_RIGHT);

        if (LMIC.txrxFlags & TXRX_DNW1) {
            display.drawString(59, 34, "1");
        } else if (LMIC.txrxFlags & TXRX_DNW2) { 
            display.drawString(59, 34, "2");
        } else {
            display.drawString(59, 34, "?");
        }


    } else if (LMIC.txrxFlags & TXRX_NACK) {

        runtime.incrementStats(false);

        display.setTextAlignment(TEXT_ALIGN_LEFT);
        display.drawString(0, 14, "NACK");

    } else {

        runtime.incrementStats(false);

        display.setTextAlignment(TEXT_ALIGN_LEFT);
        display.drawString(0, 14, "NO ACK");
    }

    if (LMIC.dataLen) {

        if (LMIC.dataLen == 3) {

            uint8_t gwc = LMIC.frame[LMIC.dataBeg];
            uint8_t gw_rssi = LMIC.frame[LMIC.dataBeg + 1];
            int8_t gw_snr = LMIC.frame[LMIC.dataBeg + 2];
    
            display.setTextAlignment(TEXT_ALIGN_LEFT);
            display.drawString(66, 14, "Tx RSSI");
            display.setTextAlignment(TEXT_ALIGN_RIGHT);
            display.drawString(128, 14, String(gw_rssi));

            display.setTextAlignment(TEXT_ALIGN_LEFT);
            display.drawString(66, 24, "Tx SNR");
            display.setTextAlignment(TEXT_ALIGN_RIGHT);
            display.drawString(128, 24, String(gw_snr));

            display.setTextAlignment(TEXT_ALIGN_LEFT);
            display.drawString(66, 34, "GWs");
            display.setTextAlignment(TEXT_ALIGN_RIGHT);
            display.drawString(128, 34, String(gwc));

        } else {
            display.setTextAlignment(TEXT_ALIGN_RIGHT);
            display.drawString(128, 14, "UNKN DATA");    
        }

    } else {
        display.setTextAlignment(TEXT_ALIGN_RIGHT);
        display.drawString(128, 14, "NO DATA");
    }

    lcd_menu_bar("", "OK");
    display.display();
}

void RxScreen::leave() {
    
}

void RxScreen::loop() {
    if (autoClose) {
        long diff = 3000 - (millis() - enterTime);

        if (diff <= 0) {
            onBPress();
        } else {
            int t = round(diff / 1000);

            display.setColor(BLACK);
            display.fillRect(0, 53, 128, 12);
            display.setColor(WHITE);

            display.setTextAlignment(TEXT_ALIGN_RIGHT);
            display.drawString(127, 52, "OK (" + String(t + 1) + ")");
            display.display();
        }
    }
}

void RxScreen::onAPress() {
    
}

void RxScreen::onBPress() {

    if (runtime.periodic) {
        runtime.periodicContinue();
    }

    screenMgr.change(&home);
}