#ifndef _DISPLAY_H
#define _DISPLAY_H

#include "main.h"

#define SCREEN_WIDTH        264
#define SCREEN_HEIGHT       176

extern void displayInit();
extern void displayMainPage();
extern void displayHello();
extern void displayF1Calendar();
extern void displayWeather();
extern void displayDate();
extern void displayMonthCalendar();
extern void displayBattery();

#endif