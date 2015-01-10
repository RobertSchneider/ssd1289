#include "LCD.h"
#include <System.h>
#include <stdlib.h>
#include <stdio.h>

ButtonInfo *buttonList = NULL;

#define LED3 1
#define LED4 2
#define LED5 4
#define LED6 8

void lcd_initLCD()
{
	SetLEDs(LED4);
	SetLEDs(LED5);
	RCC_AHB2PeriphClockCmd(RCC_AHB2Periph_RNG, ENABLE);
	RNG_Cmd(ENABLE);
	SSD1289_Init();
	DelayMS(500);
	SSD1289_Clear(Black);
	XPT2046_Init();
	DelayMS(500);
}

void addButtonList(ButtonInfo b)
{
	ButtonInfo *copy = malloc(sizeof(ButtonInfo));
	memcpy(copy, &b, sizeof(ButtonInfo));
	copy->text = malloc(strlen(b.text)+1);
	strcpy(copy->text, b.text);
	copy->text[strlen(b.text)] = 0;

	if(buttonList == NULL) buttonList = copy;
	else {
		ButtonInfo *last = buttonList;
		while (last->next != 0)
        {
            last = last->next;
        }
        last->next = copy;
	}
}

void lcd_addButton(ButtonInfo info)
{
	SSD1289_FillRect(info.x, info.y, info.w, info.h, RGB565CONVERT(0, 122, 255));
	SSD1289_DrawRect(info.x, info.y, info.w, info.h, Blue);
	int len = strlen(info.text)*8;
	int xT = info.x + (info.w-len)/2;
	int yT = info.y + (info.h-16)/2;
	SSD1289_CleanTextFont(xT, yT, info.text, White, SYSTEM_8x16);

	addButtonList(info);
}
void lcd_highlightButton(ButtonInfo *info)
{
	SSD1289_FillRect(info->x, info->y, info->w, info->h, RGB565CONVERT(100, 100, 100));
	SSD1289_DrawRect(info->x, info->y, info->w, info->h, Blue);
	int len = strlen(info->text)*8;
	int xT = info->x + (info->w-len)/2;
	int yT = info->y + (info->h-16)/2;
	SSD1289_CleanTextFont(xT, yT, info->text, White, SYSTEM_8x16);
}

void lcd_checkButton(ButtonInfo *list, Coordinate *coord)
{
	printf("check %d %d %d %d %f %f\n", list->x, list->y, list->w, list->h, coord->x, coord->y);
    if(coord->x > list->x && coord->y > list->y && coord->x < list->x+list->w && coord->y < list->y+list->h)
    {
    	//hit
    	list->target(list);
    }
}
void lcd_checkButtons(Coordinate *coord)
{
	ButtonInfo *list = buttonList;
	do 
    {
    	lcd_checkButton(list, coord);
        list = list->next;
    }while(list != 0);
}