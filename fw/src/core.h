#ifndef _core_h_
#define _core_h_

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

extern bool confirm;

#endif