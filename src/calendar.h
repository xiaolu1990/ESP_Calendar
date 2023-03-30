#ifndef _CALENDAR_H
#define _CALENDAR_H

#include "main.h"
#include <time.h>

typedef struct lunar_date_t
{
    char animals_year[10];
    char lunar_year[20];
    char lunar_date[20];
    char holiday[30];
    char suit[200];
    char avoid[200];
}lunar_date_t;

extern struct tm getCurrentDate();
extern bool isLeapYear(int year);
extern int getDaysInMonth(struct tm *date);
extern ReturnStatus_t getLunarDate(struct tm *pDate, lunar_date_t *pLunarDate);

#endif