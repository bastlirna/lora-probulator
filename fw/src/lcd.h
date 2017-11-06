#ifndef _lcd_h_
#define _lcd_h_

#include "SSD1306.h"

extern SSD1306 display;

void lcd_setup();
void lcd_update();

void lcd_menu_bar(const char*, const char*);

void lcd_menu();
void lcd_home();
void lcd_about();

void lcd_sleep();

void lcd_txs();

void lcd_menu_item(unsigned int pos, const char * label, const char * value, bool selected);

#endif