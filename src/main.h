/**
 * @brief main header file for saving macros and hardware pinouts for LuatOS ESP32-C3 development board
 * Board Link: https://wiki.luatos.com/chips/esp32c3/board.html
 *
 */
#ifndef _MAIN_H
#define _MAIN_H

#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiClient.h>
#include <ArduinoJson.h>
#include <SPI.h>
#include <Adafruit_EPD.h>
#include <Adafruit_GFX.h>
#include "Adafruit_ThinkInk.h"
#include <U8g2_for_Adafruit_GFX.h>
#include <u8g2_fonts.h>
#include <Fonts/FreeSans9pt7b.h>
#include <Fonts/FreeSansBold9pt7b.h>
#include <stdbool.h>
#include <string.h>

typedef enum ReturnStatus_t
{
    SUCCESS = 0,
    UNSUCCESS
}ReturnStatus_t;

extern ThinkInk_270_Tricolor_C44    epd;
extern U8G2_FOR_ADAFRUIT_GFX        u8g2;

#define US_TO_S_FACTOR          1000000U
#define REFRESH_INTERVAL        3600U * 4    // 4 hour

#define WIFI_SSID               "YOUR WIFI"
#define WIFI_PASSWORD           "YOUR WIFI PASSWORD"

/* 取消注释以使用和风天气, 默认使用聚合数据天气API */
// #define USE_QWEATHER

#define QWEATHER_API_KEY        "YOUR QWEATHER API KEY" // 和风天气API KEY
#define MY_CITY                 "Shanghai"
#define MY_COUNTRY_CODE         "CN"

#define JUHE_API_KEY            "YOUR API KEY"  // 聚合数据老黄历API KEY
#define JUHE_WEATHER_API_KEY    "YOUR API KEY"  // 聚合数据天气API KEY
#define MY_CITY_ZH              "上海"

// #define DST_ENABLED             1        // Winter/summer time support
#define GMT_OFFSET_SEC          3600 * 8
#define NTP_SERVER              "pool.ntp.org"  // 海外NTP server
// #define NTP_SERVER              "ntp1.aliyun.com"  // 国内NTP server


#if defined(DST_ENABLED)
#define DAYLIGHT_OFFSET_SEC     3600
#else
#define DAYLIGHT_OFFSET_SEC     0
#endif

#define SRAM_CS                 4
#define EPD_CS                  5
#define EPD_DC                  6
#define EPD_RESET               12
#define EPD_BUSY                8

#define BTN_PIN                 19
#define BATTERY_EN_PIN          13
#define BATTERY_PIN             A0

// #define BATTERY_CHECK_SUPPORT   1       // support for battery low check

#endif
