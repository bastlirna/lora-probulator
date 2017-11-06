/*******************************************************************************
 * Jan 2016 Adapted for use with ESP8266 mcu by Maarten Westenberg
 * Copyright (c) 2015 Thomas Telkamp, Matthijs Kooijman and Maarten Westenberg
 *
 * Permission is hereby granted, free of charge, to anyone
 * obtaining a copy of this document and accompanying files,
 * to do whatever they want with them without any restriction,
 * including, but not limited to, copying, modification and redistribution.
 * NO WARRANTY OF ANY KIND IS PROVIDED.
 *
 * This example sends a valid LoRaWAN packet with payload "Hello ESP world!", that
 * will be processed by The Things Network server.
 *
 * Note: LoRaWAN per sub-band duty-cycle limitation is enforced (1% in g1, 
*  0.1% in g2). 
 *
 * Change DEVADDR to a unique address! 
 * See http://thethingsnetwork.org/wiki/AddressSpace
 *
 * Do not forget to define the radio type correctly in config.h, default is:
 *   #define CFG_sx1272_radio 1
 * for SX1272 and RFM92, but change to:
 *   #define CFG_sx1276_radio 1
 * for SX1276 and RFM95.
 *
 * History: 
 * Jan 2016, Modified by Maarten to run on ESP8266. Running on Wemos D1-mini
 *******************************************************************************/
 
// Use ESP declarations. This sketch does not use WiFi stack of ESP
//  #include <ESP8266WiFi.h>
#include <ESP.h>
#include <Base64.h>

// All specific changes needed for ESP8266 need be made in hal.cpp if possible
// Include ESP environment definitions in lmic.h (lmic/limic.h) if needed
#include <lmic.h>
#include <hal/hal.h>
#include <SPI.h>

#define DEVICES_CNT 3
int g_iDevice = 0;

lmic_t LMICs[DEVICES_CNT];

// LoRaWAN Application identifier (AppEUI)
static const u1_t APPEUI[8]  = { 0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX };

// LoRaWAN DevEUI, unique device ID (LSBF)
static u1_t DEVEUI[DEVICES_CNT][8] = {
                                      { 0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX },
                                      { 0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX },
                                      { 0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX }   
                                     };

// LoRaWAN NwkSKey, network session key 
// Use this key for The Things Network
static  u1_t NWKSKEY[DEVICES_CNT][16] = {
                                         { 0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX },
                                         { 0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX },
                                         { 0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX }   
                                        };
                                             
// LoRaWAN AppSKey, application session key
// Use this key to get your data decrypted by The Things Network
static  u1_t APPSKEY[DEVICES_CNT][16] = {
                                         { 0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX },
                                         { 0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX },
                                         { 0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX }   
                                        };
                                             
// LoRaWAN end-device address (DevAddr)
// See http://thethingsnetwork.org/wiki/AddressSpace 
static u4_t DEVADDR[DEVICES_CNT] = { 0xXX011EAC, 0xXX011348, 0xXX0117AE };  //abp_nested1, abp_nested2, abp_nested3


//////////////////////////////////////////////////
// APPLICATION CALLBACKS
//////////////////////////////////////////////////

// provide application router ID (8 bytes, LSBF)
void os_getArtEui (u1_t* buf) 
{
  memcpy_P(buf, APPEUI, 8);  
}

// provide device ID (8 bytes, LSBF)
void os_getDevEui (u1_t* buf) 
{
  if(g_iDevice < DEVICES_CNT)
    memcpy(buf, DEVEUI[g_iDevice], 8);
}

static const u1_t PROGMEM APPKEY[16] = { 0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX };


// provide device key (16 bytes)
void os_getDevKey (u1_t* buf) 
{
    memcpy(buf, APPKEY, 16);
}

uint8_t mydata[] = "Hello ESP8266 world!";
static osjob_t sendjob;


/*
// Pin mapping orig
// XXX We have to see whether all these pins are really used
// if not, we can use them for real sensor work.
lmic_pinmap pins = {
  .nss = 15,      // Make D8/GPIO15, is nSS on ESP8266
  .rxtx = 2,      // D4/GPIO2. For placeholder only,
            // Do not connected on RFM92/RFM95
  .rst = 0,       // Make D0/GPIO16, Needed on RFM92/RFM95? (probably not)
  .dio = {5, 4, 3},   // Specify pin numbers for DIO0, 1, 2
            // D1/GPIO5,D2/GPIO4,D3/GPIO3 are usable pins on ESP8266
            // NOTE: D3 not really usable when UART not connected
            // As it is used during bootup and will probably not boot.
            // Leave D3 Pin unconnected for sensor to work
};

*/
// Pin mapping
// XXX We have to see whether all these pins are really used
// if not, we can use them for real sensor work.
const lmic_pinmap lmic_pins = {
  .nss = 15,      // Make D8/GPIO15, is nSS on ESP8266
  .rxtx = 0xff,      // D4/GPIO2. For placeholder only,
            // Do not connected on RFM92/RFM95
  .rst = 0xff,       // Make D0/GPIO16, Needed on RFM92/RFM95? (probably not)
  .dio = {5, 4, 0xff},    // Specify pin numbers for DIO0, 1, 2
            // D1/GPIO5,D2/GPIO4,D3/GPIO3 are usable pins on ESP8266
            // NOTE: D3 not really usable when UART not connected
            // As it is used during bootup and will probably not boot.
            // Leave D3 Pin unconnected for sensor to work
};


void onEvent(ev_t ev) {

  switch (ev) {
  case EV_SCAN_TIMEOUT:
    Serial.println(F("EV_SCAN_TIMEOUT"));
    break;
  case EV_BEACON_FOUND:
    Serial.println(F("EV_BEACON_FOUND"));
    break;
  case EV_BEACON_MISSED:
    Serial.println(F("EV_BEACON_MISSED"));
    break;
  case EV_BEACON_TRACKED:
    Serial.println(F("EV_BEACON_TRACKED"));
    break;
  case EV_JOINING:
    Serial.println(F("EV_JOINING"));
    break;
  case EV_JOINED:
    Serial.println(F("EV_JOINED"));

    // Disable link check validation (automatically enabled
    // during join, but not supported by TTN at this time).
  //  LMIC_setLinkCheckMode(0);
    break;
  case EV_RFU1:
    Serial.println(F("EV_RFU1"));
    break;
  case EV_JOIN_FAILED:
    Serial.println(F("EV_JOIN_FAILED"));
    break;
  case EV_REJOIN_FAILED:
    Serial.println(F("EV_REJOIN_FAILED"));
    break;
    break;
  case EV_TXCOMPLETE:
    Serial.println(F("EV_TXCOMPLETE (includes waiting for RX windows)"));
    if (LMIC.txrxFlags & TXRX_ACK)
      Serial.println(F("Received ack"));
    if (LMIC.dataLen) {
      // data received in rx slot after tx
      Serial.print(F("Received "));
      Serial.print(LMIC.dataLen);
      Serial.print(F(" bytes of payload: 0x"));
      for (int i = 0; i < 50; i++)
      {
        digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
        delay(20);                       
        digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
        delay(20);

      }
      for (int i = 0; i < LMIC.dataLen; i++) 
      {
        if (LMIC.frame[LMIC.dataBeg + i] < 0x10) 
        {
          Serial.print(F("0"));
        }
        Serial.print(LMIC.frame[LMIC.dataBeg + i], HEX);
      }
      Serial.println();
      printf("RSSI: %d \n", LMIC.rssi);
      printf("SNR: %d \n", LMIC.snr);
      printf("Freq: %d \n", LMIC.freq);
      printf("TXpow: %d dBm\n", LMIC.txpow);
      printf("globalDutyRate: %d \n", LMIC.globalDutyRate);
      printf("globalDutyAvail: %d \n", LMIC.globalDutyAvail);
      printf("datarate: %d \n", LMIC.datarate);
      ostime_t airtime = calcAirTime(LMIC.rps, LMIC.dataLen);
      printf("Air time: %d.", airtime / 100);
      printf("%d ms\n", airtime % 100);

      Serial.println();
    }
    else
     Serial.println(F("No data received "));
    // Schedule next transmission
    mydata[0] = 170 + os_getRndU1() % 80;
    mydata[1] = 50 + os_getRndU1() % 50;

    //store current state of radio module
    os_setTimedCallback(&sendjob, os_getTime() + sec2osticks(0), do_send);
    
    
    LMICs[g_iDevice] = LMIC;

    g_iDevice++;
    g_iDevice %= 3;

    Serial.print("Switching to device: ");
    Serial.println(g_iDevice);
    LMIC = LMICs[g_iDevice];
    

    break;
  case EV_LOST_TSYNC:
    Serial.println(F("EV_LOST_TSYNC"));
    break;
  case EV_RESET:
    Serial.println(F("EV_RESET"));
    break;
  case EV_RXCOMPLETE:
    // data received in ping slot
    Serial.println(F("EV_RXCOMPLETE"));
    break;
  case EV_LINK_DEAD:
    Serial.println(F("EV_LINK_DEAD"));
    break;
  case EV_LINK_ALIVE:
    Serial.println(F("EV_LINK_ALIVE"));
    break;
  default:
    Serial.println(F("Unknown event"));
    break;
  }
}
void do_send(osjob_t* j){
      Serial.print("Time: ");
      Serial.println(millis() / 1000);
      // Show TX channel (channel numbers are local to LMIC)
      Serial.print("Send, txCnhl: ");
      Serial.println(LMIC.txChnl);
      Serial.print("Opmode check: ");
      // Check if there is not a current TX/RX job running
    if (LMIC.opmode & (1 << 7)) 
    {
      Serial.println("OP_TXRXPEND, not sending");
    } 
    else 
    {
      Serial.println("ok");
      // Prepare upstream data transmission at the next possible time.
      LMIC_setTxData2(1, mydata, sizeof(mydata)-1, 0);
    }
    // Schedule a timed job to run at the given timestamp (absolute system time)
    //os_setTimedCallback(j, os_getTime()+sec2osticks(10), do_send);
         
}

void setup()
{
  Serial.begin(115200);
  Serial.println(F("Starting"));

  // LMIC init
  os_init();
  // Reset the MAC state. Session and pending data transfers will be discarded.
  LMIC_reset();

  // Set static session parameters. Instead of dynamically establishing a session
  // by joining the network, precomputed session parameters are be provided.
  LMIC_setSession(0x1, DEVADDR[0], NWKSKEY[0], APPSKEY[0]);

#if defined(CFG_eu868)
  // Set up the channels used by the Things Network, which corresponds
  // to the defaults of most gateways. Without this, only three base
  // channels from the LoRaWAN specification are used, which certainly
  // works, so it is good for debugging, but can overload those
  // frequencies, so be sure to configure the full frequency range of
  // your network here (unless your network autoconfigures them).
  // Setting up channels should happen after LMIC_setSession, as that
  // configures the minimal channel set.
  // NA-US channels 0-71 are configured automatically
  LMIC_setupChannel(0, 868100000, DR_RANGE_MAP(DR_SF12, DR_SF7), BAND_CENTI);      // g-band
  LMIC_setupChannel(1, 868300000, DR_RANGE_MAP(DR_SF12, DR_SF7B), BAND_CENTI);      // g-band
  LMIC_setupChannel(2, 868500000, DR_RANGE_MAP(DR_SF12, DR_SF7), BAND_CENTI);      // g-band
  LMIC_setupChannel(3, 867100000, DR_RANGE_MAP(DR_SF12, DR_SF7), BAND_CENTI);      // g-band
  LMIC_setupChannel(4, 867300000, DR_RANGE_MAP(DR_SF12, DR_SF7), BAND_CENTI);      // g-band
  LMIC_setupChannel(5, 867500000, DR_RANGE_MAP(DR_SF12, DR_SF7), BAND_CENTI);      // g-band
  LMIC_setupChannel(6, 867700000, DR_RANGE_MAP(DR_SF12, DR_SF7), BAND_CENTI);      // g-band
  LMIC_setupChannel(7, 867900000, DR_RANGE_MAP(DR_SF12, DR_SF7), BAND_CENTI);      // g-band
  LMIC_setupChannel(8, 868800000, DR_RANGE_MAP(DR_FSK, DR_FSK), BAND_MILLI);      // g2-band
                                          // TTN defines an additional channel at 869.525Mhz using SF9 for class B
                                          // devices' ping slots. LMIC does not have an easy way to define set this
                                          // frequency and support for class B is spotty and untested, so this
                                          // frequency is not configured here.
#endif                                          
  // Disable link check validation
  LMIC_setLinkCheckMode(0);

  // TTN uses SF12 for its RX2 window.
  LMIC.dn2Dr = DR_SF9;

  // Set data rate and transmit power for uplink (note: txpow seems to be ignored by the library)
  LMIC_setDrTxpow(DR_SF7, 14);// DR_SF7B



  for(int i = 0; i < DEVICES_CNT; i++)
    LMICs[i] = LMIC;



  for(int i = 1; i < DEVICES_CNT; i++)
  {
    LMICs[i].devaddr = DEVADDR[i];
    os_copyMem(LMICs[i].nwkKey, NWKSKEY[i], 16);
    os_copyMem(LMICs[i].artKey, APPSKEY[i], 16);
  }


  // Start job
  do_send(&sendjob);
}

//
void loop() 
{
 
  os_runloop_once();
}
