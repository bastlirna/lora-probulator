#include "tx.h"

#include "Arduino.h"
#include "hal.h"
#include "lcd.h"
#include "core.h"
#include "lora.h"

#include "imgs/icons.h"

Animation an(&display, (128 - waits_0_width) / 2, 20, waits_0_width, waits_0_height);

char* wf[3] = { waits_1_bits, waits_2_bits, waits_3_bits };


/*

Show:

    message up counter
    payload type
    payload content (?)
    message port
    devace name
    confirm Yes/No

*/

void TxScreen::enter() {

    lcd_txs();
/*
    Serial.print("Send, txCnhl: ");
    Serial.println(LMIC.txChnl);
    Serial.print("Opmode check: ");
*/

/*
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
*/
    // device
    display.setTextAlignment(TEXT_ALIGN_CENTER);
    display.drawString(64, 0, "SENDING");

    display.setTextAlignment(TEXT_ALIGN_LEFT);
    switch (settings.payloadType) {
        case PayloadEmpty:
            display.drawString(0, 37, "P: Empty");
            break;
        case Payload42:
            display.drawString(0, 37, "P: 0x42");
            break;
        case PayloadTxt:
            display.drawString(0, 37, "P: TXT");
            break;
        case PayloadCounter:
            display.drawString(0, 37, "P: CTN");
            break;
        case PayloadMax:
            display.drawString(0, 37, "P: MAX");
            break;
    }

    // confirm
    if (settings.confirm) {
        display.drawXbm(116, 38, ICON(ack));
    }

    an.play();

    display.display();

    an.setInterval(400);
    an.setFrames(wf, 3);
    an.play();


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
    an.loop();
}

void TxScreen::onAPress() {

    if (runtime.periodic) {
        runtime.periodicStop();
    }

    lora_reset();
    screenMgr.change(&home);
}
