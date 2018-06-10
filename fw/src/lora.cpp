#include "lora.h"

#include "hal.h"

#include "Arduino.h"
#include "core.h"

#include <lmic.h>
#include <hal/hal.h>
#include <SPI.h>

#include "lora_keys.h"

//uint8_t mydata[] = "Hello ESP8266 world!";
static osjob_t sendjob;

// --- LMIC hal settings ------------------------------------------------------

// Pin mapping
// XXX We have to see whether all these pins are really used
// if not, we can use them for real sensor work.

lmic_pinmap pins = {
    .nss = PIN_RFM95_NSS,                          // Make D8/GPIO15, is nSS on ESP8266
    .rxtx = 0xff,                                  // D4/GPIO2. For placeholder only,
                                                   // Do not connected on RFM92/RFM95
    .rst = 0xff,                                   // Make D0/GPIO16, Needed on RFM92/RFM95? (probably not)
    .dio = {PIN_RFM95_DIO0, PIN_RFM95_DIO1, 0xff}, // Specify pin numbers for DIO0, 1, 2
                                                   // D1/GPIO5,D2/GPIO4,D3/GPIO3 are usable pins on ESP8266
                                                   // NOTE: D3 not really usable when UART not connected
                                                   // As it is used during bootup and will probably not boot.
                                                   // Leave D3 Pin unconnected for sensor to work
};

// --- LMIC value callbacks ---------------------------------------------------

// TODO os_getXXX callbacks are only for OTAA,

// Provide the application EUI (8 bytes, LSBF)
void os_getArtEui(u1_t *buf)
{
    memcpy(buf, LORA_DEVS[settings.currentDev].APPEUI, 8);
}

// Provide device EUI (8 bytes, LSBF)
void os_getDevEui(u1_t *buf)
{
    memcpy(buf, LORA_DEVS[settings.currentDev].DEVEUI, 8);
}

// provide device key (16 bytes)
void os_getDevKey(u1_t *buf)
{
    memcpy(buf, LORA_DEVS[settings.currentDev].APPKEY, 16);
}

// --- LMIC event callbacks ---------------------------------------------------

static void on_txcomplete()
{
    if (settings.confirm || settings.donwlink)
    {
        screenMgr.change(&rxs);
    }
    else
    {
        if (runtime.periodic)
        {
            runtime.periodicContinue();
            runtime.incrementStats(false);
        }
        screenMgr.change(&home);
    }

    /*
    if (LMIC.txrxFlags & TXRX_ACK) {

      //Serial.println(F("Received ack"));
      //Serial.println();
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

    }

    if (LMIC.dataLen) {
      // data received in rx slot after tx
      //Serial.print(F("Received "));
      //Serial.print(LMIC.dataLen);
      //Serial.print(F(" bytes of payload: 0x"));
    }
    else
    {
     //Serial.print(F("No data received "));
    }
    */

    // Schedule next transmission
    //mydata[0] = 170 + os_getRndU1() % 80;
    //mydata[1] = 50 + os_getRndU1() % 50;
    //os_setTimedCallback(&sendjob, os_getTime() + sec2osticks(0), do_send);
}

// Trigger actions based on the event and the LMIC state
void onEvent(ev_t ev)
{
    switch (ev)
    {
    case EV_SCAN_TIMEOUT:
        //Serial.println(F("EV_SCAN_TIMEOUT"));
        break;
    case EV_BEACON_FOUND:
        //Serial.println(F("EV_BEACON_FOUND"));
        break;
    case EV_BEACON_MISSED:
        //Serial.println(F("EV_BEACON_MISSED"));
        break;
    case EV_BEACON_TRACKED:
        //Serial.println(F("EV_BEACON_TRACKED"));
        break;
    case EV_JOINING:
        //Serial.println(F("EV_JOINING"));
        break;
    case EV_JOINED:
        //Serial.println(F("EV_JOINED"));
        break;
    case EV_RFU1:
        //Serial.println(F("EV_RFU1"));
        break;
    case EV_JOIN_FAILED:
        //Serial.println(F("EV_JOIN_FAILED"));
        break;
    case EV_REJOIN_FAILED:
        //Serial.println(F("EV_REJOIN_FAILED"));
        break;
    case EV_TXCOMPLETE:
        //Serial.println(F("EV_TXCOMPLETE (includes waiting for RX windows)"));
        on_txcomplete();
        break;
    case EV_LOST_TSYNC:
        //Serial.println(F("EV_LOST_TSYNC"));
        break;
    case EV_RESET:
        //Serial.println(F("EV_RESET"));
        break;
    case EV_RXCOMPLETE:
        // data received in ping slot
        //Serial.println(F("EV_RXCOMPLETE"));
        break;
    case EV_LINK_DEAD:
        //Serial.println(F("EV_LINK_DEAD"));
        break;
    case EV_LINK_ALIVE:
        //Serial.println(F("EV_LINK_ALIVE"));
        break;
    default:
        //Serial.println(F("Unknown event"));
        break;
    }
}

void do_send(osjob_t *j)
{
    //Serial.print("Time: ");
    //Serial.println(millis() / 1000);
    // Show TX channel (channel numbers are local to LMIC)
    //Serial.print("Send, txCnhl: ");
    //Serial.println(LMIC.txChnl);
    //Serial.print("Opmode check: ");
    // Check if there is not a current TX/RX job running
    if (LMIC.opmode & (1 << 7))
    {
        //Serial.println("OP_TXRXPEND, not sending");
    }
    else
    {
        //Serial.println("ok");
        // Prepare upstream data transmission at the next possible time.
        //LMIC_setTxData2(1, mydata, sizeof(mydata)-1, 1);
    }

    /*
    // Schedule a timed job to run at the given timestamp (absolute system time)
    os_setTimedCallback(j, os_getTime()+sec2osticks(10), do_send);
    */
}

// --- Main functions ---------------------------------------------------------

//
#define DATA_BUFFER_MAXSIZE (MAX_LEN_PAYLOAD - 1)

static uint8_t data_buffer[DATA_BUFFER_MAXSIZE];
static uint8_t data_buffer_len = 0;

static uint16_t msg_counter = 0;

void lora_setup()
{
    os_init(); // LMIC OS init
    lora_reset();
}

void lora_reset()
{
    // Reset the MAC state. Session and pending data transfers will be discarded.
    LMIC_reset();
    //Serial.println("LMIC_reet() finished");

    // Set static session parameters (ABP)
    LMIC_setSession(0x1, LORA_DEVS[settings.currentDev].DEVADDR, (uint8_t *)LORA_DEVS[settings.currentDev].NWKSKEY, (uint8_t *)LORA_DEVS[settings.currentDev].APPSKEY);
    //Serial.println("LMIC_setSession() finished");

    // Set up the channels used by the Things Network, which corresponds
    // to the defaults of most gateways. Without this, only three base
    // channels from the LoRaWAN specification are used, which certainly
    // works, so it is good for debugging, but can overload those
    // frequencies, so be sure to configure the full frequency range of
    // your network here (unless your network autoconfigures them).
    // Setting up channels should happen after LMIC_setSession, as that
    // configures the minimal channel set.
    // NA-US channels 0-71 are configured automatically
    LMIC_setupChannel(0, 868100000, DR_RANGE_MAP(DR_SF12, DR_SF7), BAND_CENTI);  // g-band
    LMIC_setupChannel(1, 868300000, DR_RANGE_MAP(DR_SF12, DR_SF7B), BAND_CENTI); // g-band
    LMIC_setupChannel(2, 868500000, DR_RANGE_MAP(DR_SF12, DR_SF7), BAND_CENTI);  // g-band
    LMIC_setupChannel(3, 867100000, DR_RANGE_MAP(DR_SF12, DR_SF7), BAND_CENTI);  // g-band
    LMIC_setupChannel(4, 867300000, DR_RANGE_MAP(DR_SF12, DR_SF7), BAND_CENTI);  // g-band
    LMIC_setupChannel(5, 867500000, DR_RANGE_MAP(DR_SF12, DR_SF7), BAND_CENTI);  // g-band
    LMIC_setupChannel(6, 867700000, DR_RANGE_MAP(DR_SF12, DR_SF7), BAND_CENTI);  // g-band
    LMIC_setupChannel(7, 867900000, DR_RANGE_MAP(DR_SF12, DR_SF7), BAND_CENTI);  // g-band
    LMIC_setupChannel(8, 868800000, DR_RANGE_MAP(DR_FSK, DR_FSK), BAND_MILLI);   // g2-band
    // TTN defines an additional channel at 869.525Mhz using SF9 for class B
    // devices' ping slots. LMIC does not have an easy way to define set this
    // frequency and support for class B is spotty and untested, so this
    // frequency is not configured here.

    // Disable data rate adaptation
    LMIC_setAdrMode(0);
    //Serial.println("LMICsetAddrMode() finished");

    // Disable link check validation
    LMIC_setLinkCheckMode(0);

    // Disable beacon tracking
    LMIC_disableTracking();

    // Stop listening for downstream data (periodical reception)
    LMIC_stopPingable();

    // Disable link check validation

    // Datarate for RX2 window (default LMIC is SF12, but TTN and many others use SF9)
    // TODO move this to LORA_DEVS setting
    // NOTE this is only for ABP, this parameter is handled in OTAA automaticaly (verify???)
    LMIC.dn2Dr = DR_SF9;

    // Set data rate and transmit power (note: txpow seems to be ignored by the library)
    LMIC_setDrTxpow(DR_SF7, 14);

    //lora_change_sf(sf);

    //
    ////Serial.flush();
    //Serial.println("Init done");

    msg_counter = 0;
}

void saveParam(u4_t value, char *name)
{
    // TODO add seqnoUp into RTC RAM memory
    //   if(strcmp(name, "seqnoUp") == 0){
    //       Serial.println("updating seq");
    //   }
}

void lora_loop()
{
    os_runloop_once();
}

void lora_off()
{
    LMIC_shutdown();
}

void lora_change_sf(uint8_t s)
{

    //LMIC_setDrTxpow(SF7, 14);

    //return;

    Serial.print("Set SF to ");
    Serial.println(s);

    switch (s)
    {
    case 7:
        //Serial.println("7");
        LMIC_setDrTxpow(SF7, 14);
        return;
    case 8:
        //Serial.println("8");
        LMIC_setDrTxpow(SF8, 14);
        return;
    case 9:
        //Serial.println("9");
        LMIC_setDrTxpow(SF9, 14);
        return;
    case 10:
        //Serial.println("10");
        LMIC_setDrTxpow(SF10, 14);
        return;
    case 11:
        //Serial.println("11");
        LMIC_setDrTxpow(SF11, 14);
        return;
    case 12:
        //Serial.println("12");
        LMIC_setDrTxpow(SF12, 14);
        return;
    defualt:
        Serial.println("UNKNOWN SF");
    }
}

const char *lora_dev_name(uint8_t id)
{
    return LORA_DEVS[id].name;
}

uint8_t lora_dev_count()
{
    return LORA_DEVS_COUNT;
}

static void lora_set_max_message()
{
    for (uint8_t i = 0; i < DATA_BUFFER_MAXSIZE; i++)
    {
        data_buffer[i] = i;
    }
    data_buffer_len = DATA_BUFFER_MAXSIZE;
}


uint8_t lora_send_message()
{
    // Check if there is not a current TX/RX job running
    if (LMIC.opmode & (1 << 7))
    {
        return 1;
    }

    LMIC.upRepeat = 1;
    msg_counter ++;

    switch(settings.payloadType)
    {
        case (PayloadEmpty):
            data_buffer[0] = 0;
            data_buffer_len = 0;
            break;

        case (Payload42):
            data_buffer[0] = 0x42;
            data_buffer_len = 1;
            break;

        case (PayloadTxt):
            strcpy((char *)data_buffer, "Lorem Ipsum");
            data_buffer_len = strlen((char *)data_buffer);
            break;

        case (PayloadCounter):
            data_buffer[0] = (uint8_t) (msg_counter);
            data_buffer[1] = (uint8_t) (msg_counter >> 8);
            data_buffer_len = 2;
            break;

        case (PayloadMax):
            lora_set_max_message();
            break;

        default:
            return 2;
    }

    // Prepare upstream data transmission at the next possible time.
    LMIC_setTxData2(settings.donwlink ? 2 : 1, data_buffer, data_buffer_len, settings.confirm ? 1 : 0);

    return 0;
}


