#ifndef _core_h_
#define _core_h_

#include <log.h>

#include <screen.h>
#include <screen/home.h>
#include <screen/menu.h>
#include <screen/about.h>
#include <screen/tx.h>
#include <screen/rx.h>
#include <screen/msg.h>

extern HomeScreen home;
extern MenuScreen menu;
extern AboutScreen about;
extern TxScreen txs;
extern RxScreen rxs;
extern MsgScreen msg;

extern ScreenMgr screenMgr;

extern Screen* currentScree;

extern int INTERVALS[];

#define INTERVALS_LEN 6
#define INTERVALS_OFF -1

enum PayloadType {
    PayloadEmpty = 0,
    Payload42,
    PayloadTxt,
    PayloadCounter,
    PayloadMax,

    _PayloadEnd
};

enum ModeType {
    ModeUpOnly = 0,
    ModeConfirmend,
    ModeMonitor,

    _ModeTypeEnd
};

struct Settings {
    bool saved;
    bool confirm;
    bool donwlink;
    PayloadType payloadType;
    ModeType mode;
    uint8_t sf;
    uint8_t currentDev;
    int16_t interval;
    bool screenMirror;
};

struct Runtime {
    bool periodic;
    bool periodicRunning;
    bool send;

    unsigned long interval;
    unsigned long lastRun;

    void loop();

    void periodicStart();
    void periodicStop();
    void periodicReset();
    void periodicContinue();

    void incrementStats(bool success);

    long countdownTime();

    unsigned int counter;
    unsigned int successCounter;
    unsigned int errorCounter;
    unsigned int successRate;
};

extern Settings settings;
extern Runtime runtime;

void core_setup();

#endif
