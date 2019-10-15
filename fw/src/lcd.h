#ifndef _lcd_h_
#define _lcd_h_

#include "SSD1306.h"
#include "display.h"

#define ICON(name) name##_width, name##_height, name##_bits

extern Display display;

void lcd_setup();
void lcd_update();

void lcd_menu_bar(const char*, const char*);

void lcd_menu();
void lcd_home();
void lcd_about();

void lcd_sleep();

void lcd_txs();

void lcd_menu_item(unsigned int pos, const char * label, String value, bool selected);



class Animation
{
public:
    Animation(Display* d, uint16_t x, uint16_t y, uint16_t w, uint16_t h) :
        disp(d), _x(x), _y(y), _w(w), _h(h)
    {
    }

    void setFrames(char** frames, uint8_t count);
    void setInterval(uint16_t ms);

    void loop();

    void play();
    void stop();
    void clear();
private:
    Display* disp;
    uint16_t _x;
    uint16_t _y;
    uint16_t _w;
    uint16_t _h;
    char** frames;
    uint8_t count;
    uint16_t interval;

    uint8_t current;
    unsigned long last;
    bool enabled;
};



#endif
