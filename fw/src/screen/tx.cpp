#include "tx.h"

#include "Arduino.h"
#include "hal.h"
#include "lcd.h"
#include "core.h"
#include "lora.h"

uint8_t mydata[] = "Hello world!";

void TxScreen::enter() {
    Serial.println("ENTER tx");

    lcd_txs();

    Serial.print("Send, txCnhl: ");
    Serial.println(LMIC.txChnl);
    Serial.print("Opmode check: ");

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
    display.drawString(60, 24, confirm ? "YES" : "NO");

    display.display();

        // Check if there is not a current TX/RX job running
    if (LMIC.opmode & (1 << 7)) 
    {
        msg.message = "OP_TXRXPEND, not sending";
        Serial.println("OP_TXRXPEND, not sending");

        screenMgr.change(&msg);
    } 
    else 
    {
        Serial.println("ok");

        LMIC.upRepeat = 1;

        // Prepare upstream data transmission at the next possible time.
        LMIC_setTxData2(confirm ? 2 : 1, mydata, sizeof(mydata)-1, confirm ? 1 : 0);
    }

}

void TxScreen::leave() {
    Serial.println("LEAVE tx");
}

void TxScreen::loop() {
}

void TxScreen::onAPress() {
    lora_reset();
    screenMgr.change(&home);
}