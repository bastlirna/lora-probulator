#include "display.h"

void Display::sendBufferOnSerial() {
    Serial.println("\n");

    uint8_t x,y;

    for (y = 0; y < (DISPLAY_HEIGHT / 8); y++) {
        for (x = 0; x < DISPLAY_WIDTH; x++) {
            uint16_t pos = x + y * DISPLAY_WIDTH;
        
            Serial.print((unsigned char)buffer[pos], HEX);
            Serial.print(" ");
        }
        yield();
    }

    Serial.println("\n");
}