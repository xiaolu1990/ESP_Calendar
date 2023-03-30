#include "utils.h"

/**
 * @brief GET request helper function
 * 
 * @param url 
 * @return String 
 */
String httpGetRqst(String url)
{
    HTTPClient http;
    String payload = "HTTP GET";
    
    http.begin(url);

    int http_code = http.GET();
    if (http_code > 0)
    {
        if (http_code == HTTP_CODE_OK)
        {
            payload = http.getString();
        }
    }

    http.end();

    return payload;
}

/**
 * @brief Checks whether battery is below threshold
 * 
 * @return bool 
 */
bool checkBatteryIsLow() 
{
    bool status = false;
    int value;

    value = analogRead(BATTERY_PIN);
    // Serial.println(value);
    if (value < 3000)   // 3200 ~ 3.0V
        status = true;
    
    return status;
}