#ifndef _display_h_
#define _display_h_

#include "SSD1306.h"

#define DISPLAY_HEIGHT 64
#define DISPLAY_WIDTH 128

class Display : public SSD1306Wire {
    using SSD1306Wire::SSD1306Wire;

    public:
        void sendBufferOnSerial();
};

#endif
