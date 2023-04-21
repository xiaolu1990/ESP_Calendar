/**
 * @file main.ino
 * @author Zhangshun.Lu
 * @brief E-ink calendar based on ESP32 that has features:
 *        1. display date and weather information
 *        2. display Chinese lunar date of today information
 *        3. display the F1 racing calendar of season 2023
 * @version 1.0
 * @date 2023-04-21
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "main.h"
#include "display.h"
#include "weather.h"
#include "calendar.h"
#include "bitmap.h"
#include "utils.h"

bool battery_is_low = false;

bool     button_pressed      = false;
uint32_t button_pressed_time = 0;
uint32_t last_pressed_time   = 0;

uint8_t page_number = 0;  // 0 = main page, 1 = sub page, ...

struct tm date_today;
lunar_date_t lunar_date_today;
weather_t weather_today;
aqi_t     aqi_today;
locationID_t location = Shanghai;

ThinkInk_270_Tricolor_C44   epd(EPD_DC, EPD_RESET, EPD_CS, SRAM_CS, EPD_BUSY);
U8G2_FOR_ADAFRUIT_GFX       u8g2;

/**
 * @brief interrupt handler for button press
 *
 */
void IRAM_ATTR isrButton()
{
    button_pressed_time = millis();
    if (button_pressed_time - last_pressed_time > 250)
    {
        if (page_number > 0)
            page_number = 0;
        else
            ++page_number;

        button_pressed = true;
        last_pressed_time = button_pressed_time;
    }
}

/**
 * @brief connect to wifi
 *
 */
void connectWiFi()
{
    Serial.begin(115200);
    Serial.print("Connect to WiFi ");

    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    while(WiFi.status() != WL_CONNECTED)
    {
        Serial.print(". ");
        delay(500);
    }

    Serial.print("\nConnected! IP address: ");
    Serial.println(WiFi.localIP());
}

void setup()
{
    pinMode(BTN_PIN, INPUT_PULLUP);
    attachInterrupt(BTN_PIN, isrButton, FALLING);

    /* Connect to Internet and Fetch the information */
    connectWiFi();

    ReturnStatus_t status;

    status = getWeather(&weather_today, location);  // weather
    if (status == SUCCESS)
    {
        Serial.println(weather_today.text);
        Serial.println(weather_today.temp);
        Serial.println(weather_today.icon);
#ifndef USE_QWEATHER
        Serial.println(weather_today.aqi);
        Serial.println(weather_today.aqi_descr);
#endif
    }
    else
    {
        Serial.println("Failed to obtain weather information");
    }

#ifdef USE_QWEATHER
//     status = getAQI(&aqi_today, location);  // AQI
//     Serial.println(aqi_today.aqi);
//     Serial.println(aqi_today.category);
#endif

    date_today = getCurrentDate();  // date

    status = getLunarDate(&date_today, &lunar_date_today);  // lunar date
    if (status == SUCCESS)
    {
        Serial.println(lunar_date_today.animals_year);
        Serial.println(lunar_date_today.lunar_year);
        Serial.println(lunar_date_today.lunar_date);
        Serial.println(lunar_date_today.holiday);
        Serial.println(lunar_date_today.suit);
        Serial.println(lunar_date_today.avoid);
    }
    else
    {
        Serial.println("Failed to obtaian lunar information");
    }

//     /* Check battery voltage */
// #if defined(BATTERY_CHECK_SUPPORT)
//     battery_is_low = checkBatteryIsLow();
// #endif

    /* Display Information on EPD */
    displayInit();

    displayMainPage();

    /* Auto reboot device every 4 hours*/
    // esp_sleep_enable_timer_wakeup(US_TO_S_FACTOR * REFRESH_INTERVAL);
    // Serial.flush();
    // esp_deep_sleep_start();
}

void loop()
{
    if (button_pressed)
    {
        switch (page_number)
        {
        case 0:
            displayMainPage();
            break;
        case 1:
            displayF1Calendar();
            break;
        default:
            break;
        }

        button_pressed = false;
    }
}
