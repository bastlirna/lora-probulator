#ifndef _lora_h_
#define _lora_h_

#include <lmic.h>

//uint8_t mydata[] = "Hello ESP8266 world!";

struct LoraDevice {
    const char * name;
    const u1_t APPEUI[8];
    const u1_t DEVEUI[8];
    const u1_t NWKSKEY[16];
    const u1_t APPSKEY[16];
    const u4_t DEVADDR;
    const u1_t APPKEY[16];

};

void onEvent(ev_t ev);

void lora_setup();
void lora_reset();
void lora_loop();

void lora_off();
void lora_change_sf(uint8_t s);
const char * lora_dev_name(uint8_t id);
uint8_t lora_dev_count();

uint8_t lora_send_message();

#endif
