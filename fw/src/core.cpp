#include "core.h"

//RTC_DATA_ATTR int bootCount = 0;

HomeScreen home = HomeScreen();
MenuScreen menu = MenuScreen();
AboutScreen about = AboutScreen();
TxScreen txs = TxScreen();
RxScreen rxs = RxScreen();
MsgScreen msg = MsgScreen();

ScreenMgr screenMgr = ScreenMgr();

// RTC_DATA_ATTR bool confirm = false;
// RTC_DATA_ATTR bool donwlink = false;
// RTC_DATA_ATTR uint8_t sf = 7; /* 7 - 12 */
// RTC_DATA_ATTR uint8_t currentDev = 0;

int INTERVALS[] = { 5, 10, 30, 60, 300, 600 };

RTC_DATA_ATTR Settings settings = {
    saved: false
};

RTC_DATA_ATTR Runtime runtime = {
};

void core_setup() {

    // initialization after reset
    if (settings.saved == false) {

        settings.saved = true;

        settings.confirm = true;
        settings.donwlink = false;
        settings.sf = 7;
        settings.currentDev = 0;
        settings.interval = INTERVALS_OFF;

        runtime.periodic = false;
        runtime.periodicRunning = false;
        runtime.send = false;
    }
}

void Runtime::loop() {
    if (periodicRunning && !send) {

        if (countdownTime() < 0) {
            send = true;
        }
    }
}

void Runtime::periodicStart() {
    periodicRunning = true;
    lastRun = millis();
    interval = INTERVALS[settings.interval] * 1000;

    rxs.autoClose = true;
}

void Runtime::periodicStop() {
    periodicRunning = false;

    rxs.autoClose = false;
}

void Runtime::periodicContinue() {
    send = false;
    lastRun = millis();
}

void Runtime::periodicReset() {
    counter = 0;
    successCounter = 0;
}

void Runtime::incrementStats(bool success) {
    counter ++;

    if (success) {
        successCounter ++;
    }

    if (counter > 0) {
        float rate = ((float)successCounter / counter) * 100;

        successRate = round(rate);
    } else {
        successRate = 0;
    }
}

long Runtime::countdownTime() {
    unsigned long d = millis() - lastRun;
    return interval - d;
}
