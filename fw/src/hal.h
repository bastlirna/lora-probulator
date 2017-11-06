#ifndef _HAL_H_
#define _HAL_H_

#include <Button.h>
#include <Bounce2.h>

// pin deffinition

#define PIN_BTN_A 33
#define PIN_BTN_B 34
#define PIN_BTN_OFF 36

// RFM95 pins

#define PIN_RFM95_NSS 5
#define PIN_RFM95_DIO0 39
#define PIN_RFM95_DIO1 32

// 

extern Button btnA;
extern Button btnB;
extern Bounce btnOff;

void hal_setup();
void hal_loop();

#endif