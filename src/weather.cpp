#include "weather.h"
#include "utils.h"
#include "bitmap.h"

/**
 * @brief Get the current weather using QWeather API or Juhe API
 *
 * @param pWeather
 * @param locationID
 * @return ReturnStatus_t
 */
ReturnStatus_t getWeather(weather_t *pWeather, locationID_t locationID)
{
#ifdef USE_QWEATHER
    String url = "https://devapi.qweather.com/v7/weather/now?location=" + (String) locationID + "&key=" + QWEATHER_API_KEY + "&gzip=n";
#else
    String url = "http://apis.juhe.cn/simpleWeather/query?city=" + (String) MY_CITY_ZH + "&key=" + JUHE_WEATHER_API_KEY;
#endif

    // Serial.println(url);

    String payload = httpGetRqst(url);

    // Serial.println(payload);

    ReturnStatus_t status = SUCCESS;

    StaticJsonDocument <2000> doc;

    DeserializationError error = deserializeJson(doc, payload);
    if (error)
    {
        Serial.print("deserializeJson() failed: ");
        Serial.println(error.c_str());
    }

#ifdef USE_QWEATHER
    const char* code = doc["code"];
    if (strcmp(code, "200"))
    {
        Serial.print("Failed to obtain stream, return status code: ");
        Serial.println(code);
        status = UNSUCCESS;
    }

    /* Return Success, assign value to weather object */
    strcpy(pWeather->icon, doc["now"]["icon"]);
    strcpy(pWeather->temp, doc["now"]["temp"]);
    strcpy(pWeather->text, doc["now"]["text"]);
#else
    const char* reason = doc["reason"];
    if (strcmp(reason, "查询成功!"))
    {
        Serial.print("Failed to obtain stream, return status code: ");
        Serial.println(reason);
        status = UNSUCCESS;
    }

    /* Return Success, assign value to weather object */
    strcpy(pWeather->icon, doc["result"]["realtime"]["wid"]);
    strcpy(pWeather->temp, doc["result"]["realtime"]["temperature"]);
    strcpy(pWeather->text, doc["result"]["realtime"]["info"]);
    strcpy(pWeather->aqi, doc["result"]["realtime"]["aqi"]);

    int aqi = atoi(pWeather->aqi);
    if (aqi <= 50)
        strcpy(pWeather->aqi_descr, "优");
    else if ((aqi > 50) && (aqi <=100))
        strcpy(pWeather->aqi_descr, "良");
    else if ((aqi > 100) && (aqi <=150))
        strcpy(pWeather->aqi_descr, "轻度污染");
    else if ((aqi > 150) && (aqi <=200))
        strcpy(pWeather->aqi_descr, "中度污染");
    else if ((aqi > 200) && (aqi <=300))
        strcpy(pWeather->aqi_descr, "重度污染");
    else if (aqi > 300)
        strcpy(pWeather->aqi_descr, "严重污染");


#endif


    return status;
}

/**
 * @brief Get the Air Quality Index information of the location
 *
 * @param pAQI
 * @param locationID
 * @return ReturnStatus_t
 */
ReturnStatus_t getAQI(aqi_t *pAQI, locationID_t locationID)
{
    String url = "https://devapi.qweather.com/v7/air/now?location=" + (String) locationID + "&key=" + QWEATHER_API_KEY + "&gzip=n";

    String payload = httpGetRqst(url);

    ReturnStatus_t status = SUCCESS;

    StaticJsonDocument <512> doc;

    DeserializationError error = deserializeJson(doc, payload);
    if (error)
    {
        Serial.print("deserializeJson() failed: ");
        Serial.println(error.c_str());
    }

    const char* code = doc["code"];
    if (strcmp(code, "200"))
    {
        Serial.print("Failed to obtain stream, return status code: ");
        Serial.println(code);
        status = UNSUCCESS;
    }

    /* Return Success, assign value to weather object */
    strcpy(pAQI->aqi, doc["now"]["aqi"]);
    strcpy(pAQI->category, doc["now"]["category"]);

    return status;
}

/**
 * @brief Get the weather icon bitmap
 *
 * @param iconCode
 * @return unsigned char*
 */
unsigned char *getWeatherIcon(char *iconCode)
{
    unsigned char *iconBitmap;

    if ((strstr(iconCode, "100")) || (strstr(iconCode, "00")))  // 晴
        iconBitmap = (unsigned char*) Bitmap_100_fill;
    else if ((strstr(iconCode, "101")) || (strstr(iconCode, "01"))) // 多云
        iconBitmap = (unsigned char*) Bitmap_101_fill;
    else if (strstr(iconCode, "102"))
        iconBitmap = (unsigned char*) Bitmap_102_fill;
    else if (strstr(iconCode, "103"))
        iconBitmap = (unsigned char*) Bitmap_103_fill;
    else if ((strstr(iconCode, "104")) || (strstr(iconCode, "02"))) // 阴
        iconBitmap = (unsigned char*) Bitmap_104_fill;
    else if (strstr(iconCode, "150"))
        iconBitmap = (unsigned char*) Bitmap_150_fill;
    else if (strstr(iconCode, "151"))
        iconBitmap = (unsigned char*) Bitmap_151_fill;
    else if (strstr(iconCode, "152"))
        iconBitmap = (unsigned char*) Bitmap_152_fill;
    else if (strstr(iconCode, "153"))
        iconBitmap = (unsigned char*) Bitmap_153_fill;
    else if ((strstr(iconCode, "300")) || (strstr(iconCode, "03"))) // 阵雨
        iconBitmap = (unsigned char*) Bitmap_300_fill;
    else if (strstr(iconCode, "301"))
        iconBitmap = (unsigned char*) Bitmap_301_fill;
    else if ((strstr(iconCode, "302")) || (strstr(iconCode, "04"))) // 雷阵雨
        iconBitmap = (unsigned char*) Bitmap_302_fill;
    else if (strstr(iconCode, "303"))
        iconBitmap = (unsigned char*) Bitmap_303_fill;
    else if ((strstr(iconCode, "304")) || (strstr(iconCode, "05"))) // 雷阵雨有冰雹
        iconBitmap = (unsigned char*) Bitmap_304_fill;
    else if ((strstr(iconCode, "305")) || (strstr(iconCode, "07"))) // 小雨
        iconBitmap = (unsigned char*) Bitmap_305_fill;
    else if ((strstr(iconCode, "306")) || (strstr(iconCode, "08"))) // 中雨
        iconBitmap = (unsigned char*) Bitmap_306_fill;
    else if ((strstr(iconCode, "307")) || (strstr(iconCode, "09")))  // 大雨
        iconBitmap = (unsigned char*) Bitmap_307_fill;
    else if (strstr(iconCode, "308"))
        iconBitmap = (unsigned char*) Bitmap_308_fill;
    else if (strstr(iconCode, "309"))
        iconBitmap = (unsigned char*) Bitmap_309_fill;
    else if ((strstr(iconCode, "310")) || (strstr(iconCode, "10"))) // 暴雨
        iconBitmap = (unsigned char*) Bitmap_310_fill;
    else if ((strstr(iconCode, "311")) || (strstr(iconCode, "11"))) // 大暴雨
        iconBitmap = (unsigned char*) Bitmap_311_fill;
    else if ((strstr(iconCode, "312")) || (strstr(iconCode, "12"))) // 特大暴雨
        iconBitmap = (unsigned char*) Bitmap_312_fill;
    else if ((strstr(iconCode, "313")) || (strstr(iconCode, "19"))) // 冻雨
        iconBitmap = (unsigned char*) Bitmap_313_fill;
    else if ((strstr(iconCode, "314")) || (strstr(iconCode, "21"))) // 小到中雨
        iconBitmap = (unsigned char*) Bitmap_314_fill;
    else if ((strstr(iconCode, "315")) || (strstr(iconCode, "22"))) // 中到大雨
        iconBitmap = (unsigned char*) Bitmap_315_fill;
    else if ((strstr(iconCode, "316")) || (strstr(iconCode, "23"))) // 大到暴雨
        iconBitmap = (unsigned char*) Bitmap_316_fill;
    else if ((strstr(iconCode, "317")) || (strstr(iconCode, "24"))) // 暴雨到大暴雨
        iconBitmap = (unsigned char*) Bitmap_317_fill;
    else if ((strstr(iconCode, "318")) || (strstr(iconCode, "25"))) // 大暴雨到特大暴雨
        iconBitmap = (unsigned char*) Bitmap_318_fill;
    else if (strstr(iconCode, "350"))
        iconBitmap = (unsigned char*) Bitmap_350_fill;
    else if (strstr(iconCode, "351"))
        iconBitmap = (unsigned char*) Bitmap_351_fill;
    else if (strstr(iconCode, "399"))
        iconBitmap = (unsigned char*) Bitmap_399_fill;
    else if ((strstr(iconCode, "400")) || (strstr(iconCode, "14"))) // 小雪
        iconBitmap = (unsigned char*) Bitmap_400_fill;
    else if ((strstr(iconCode, "401")) || (strstr(iconCode, "15"))) // 中雪
        iconBitmap = (unsigned char*) Bitmap_401_fill;
    else if ((strstr(iconCode, "402")) || (strstr(iconCode, "16"))) // 大雪
        iconBitmap = (unsigned char*) Bitmap_402_fill;
    else if ((strstr(iconCode, "403")) || (strstr(iconCode, "17"))) // 暴雪
        iconBitmap = (unsigned char*) Bitmap_403_fill;
    else if ((strstr(iconCode, "404")) || (strstr(iconCode, "06"))) // 雨夹雪
        iconBitmap = (unsigned char*) Bitmap_404_fill;
    else if (strstr(iconCode, "405"))
        iconBitmap = (unsigned char*) Bitmap_405_fill;
    else if (strstr(iconCode, "406"))
        iconBitmap = (unsigned char*) Bitmap_406_fill;
    else if ((strstr(iconCode, "407")) || (strstr(iconCode, "13"))) // 阵雪
        iconBitmap = (unsigned char*) Bitmap_407_fill;
    else if ((strstr(iconCode, "408")) || (strstr(iconCode, "26"))) // 小到中雪
        iconBitmap = (unsigned char*) Bitmap_408_fill;
    else if ((strstr(iconCode, "409")) || (strstr(iconCode, "27"))) // 中到大雪
        iconBitmap = (unsigned char*) Bitmap_409_fill;
    else if ((strstr(iconCode, "410")) || (strstr(iconCode, "28"))) // 大到暴雪
        iconBitmap = (unsigned char*) Bitmap_410_fill;
    else if (strstr(iconCode, "456"))
        iconBitmap = (unsigned char*) Bitmap_456_fill;
    else if (strstr(iconCode, "457"))
        iconBitmap = (unsigned char*) Bitmap_457_fill;
    else if (strstr(iconCode, "499"))
        iconBitmap = (unsigned char*) Bitmap_499_fill;
    else if (strstr(iconCode, "500"))
        iconBitmap = (unsigned char*) Bitmap_500_fill;
    else if ((strstr(iconCode, "501")) || (strstr(iconCode, "18")))  // 雾
        iconBitmap = (unsigned char*) Bitmap_501_fill;
    else if ((strstr(iconCode, "502")) || (strstr(iconCode, "53"))) // 霾
        iconBitmap = (unsigned char*) Bitmap_502_fill;
    else if ((strstr(iconCode, "503")) || (strstr(iconCode, "30"))) // 扬沙
        iconBitmap = (unsigned char*) Bitmap_503_fill;
    else if ((strstr(iconCode, "504")) || (strstr(iconCode, "29"))) // 浮沉
        iconBitmap = (unsigned char*) Bitmap_504_fill;
    else if ((strstr(iconCode, "507")) || (strstr(iconCode, "20"))) // 沙城暴
        iconBitmap = (unsigned char*) Bitmap_507_fill;
    else if ((strstr(iconCode, "508")) || (strstr(iconCode, "31"))) // 强沙尘暴
        iconBitmap = (unsigned char*) Bitmap_508_fill;
    else if (strstr(iconCode, "509"))
        iconBitmap = (unsigned char*) Bitmap_509_fill;
    else if (strstr(iconCode, "510"))
        iconBitmap = (unsigned char*) Bitmap_510_fill;
    else if (strstr(iconCode, "511"))
        iconBitmap = (unsigned char*) Bitmap_511_fill;
    else if (strstr(iconCode, "512"))
        iconBitmap = (unsigned char*) Bitmap_512_fill;
    else if (strstr(iconCode, "513"))
        iconBitmap = (unsigned char*) Bitmap_513_fill;
    else if (strstr(iconCode, "514"))
        iconBitmap = (unsigned char*) Bitmap_514_fill;
    else if (strstr(iconCode, "515"))
        iconBitmap = (unsigned char*) Bitmap_515_fill;
    else if (strstr(iconCode, "900"))
        iconBitmap = (unsigned char*) Bitmap_900_fill;
    else if (strstr(iconCode, "901"))
        iconBitmap = (unsigned char*) Bitmap_901_fill;
    else iconBitmap = (unsigned char*) Bitmap_999_fill;

    return iconBitmap;
}
