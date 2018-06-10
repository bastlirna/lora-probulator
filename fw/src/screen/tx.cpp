#include "tx.h"

#include "Arduino.h"
#include "hal.h"
#include "lcd.h"
#include "core.h"
#include "lora.h"

void TxScreen::enter() {


    lcd_txs();
/*
    Serial.print("Send, txCnhl: ");
    Serial.println(LMIC.txChnl);
    Serial.print("Opmode check: ");
*/
    display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.drawString(0, 12, "Tx Chnl");

    display.setTextAlignment(TEXT_ALIGN_RIGHT);
    display.drawString(60, 12, String(LMIC.txChnl));

    // display.setTextAlignment(TEXT_ALIGN_LEFT);
    // display.drawString(0, 22, "Tx Ctn");

    // display.setTextAlignment(TEXT_ALIGN_RIGHT);
    // display.drawString(60, 22, String(LMIC.txCnt));


    display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.drawString(0, 24, "Confirm");

    display.setTextAlignment(TEXT_ALIGN_RIGHT);
    display.drawString(60, 24, settings.confirm ? "YES" : "NO");

    display.display();


    uint8_t s = lora_send_message();
    if (s != 0) {
        // TODO handle error code
        msg.message = "OP_TXRXPEND, not sending";
        screenMgr.change(&msg);
    }
}

void TxScreen::leave() {
    //Serial.println("LEAVE tx");
}

void TxScreen::loop() {
}

void TxScreen::onAPress() {

    if (runtime.periodic) {
        runtime.periodicStop();
    }

    lora_reset();
    screenMgr.change(&home);
}
