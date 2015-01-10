#ifndef _LCD_H_
#define _LCD_H_

#include "main.h"
#include "SSD1289.h"
#include "XPT2046.h"

typedef	struct BUTTON
{
   void (*target)(struct BUTTON*);
   int tag;
   int x, y, w, h;
   char *text;
   struct BUTTON *next;
} ButtonInfo; 

void lcd_initLCD();
void lcd_checkButtons(Coordinate *coord);
void lcd_addButton(ButtonInfo info);
void lcd_highlightButton(ButtonInfo *info);

#endif