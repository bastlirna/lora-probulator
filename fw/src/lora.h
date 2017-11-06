#ifndef _lora_h_
#define _lora_h_

#include <lmic.h>

//uint8_t mydata[] = "Hello ESP8266 world!";

void onEvent(ev_t ev);

void lora_setup();
void lora_reset();
void lora_loop();

void lora_off();

#endif
