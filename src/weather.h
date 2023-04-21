#ifndef _WEATHER_H
#define _WEATHER_H

#include "main.h"

#define ICON_SIZE   32  // 32x32 weather icon size

typedef struct weather
{
    char text[50];
    char icon[5];
    char temp[5];
    char aqi[5];
    char aqi_descr[30];
}weather_t;

typedef struct aqi
{
    char aqi[5];
    char category[29];
}aqi_t;

typedef enum locationID_t
{
    Shanghai = 101020100,
    Beijing  = 101010100
}locationID_t;

extern ReturnStatus_t getWeather(weather_t *pWeather, locationID_t locationID);
extern ReturnStatus_t getAQI(aqi_t *pAQI, locationID_t locationID);
extern unsigned char *getWeatherIcon(char *iconCode);

#endif  /* _WEATHER_H */
