#include "calendar.h"
#include "utils.h"

/**
 * @brief get the date of today
 * 
 * @return struct tm 
 */
struct tm getCurrentDate()
{
    struct tm date;

    configTime(GMT_OFFSET_SEC, DAYLIGHT_OFFSET_SEC, NTP_SERVER);

    if (!getLocalTime(&date))
    {
        Serial.println("Failed to obtain time");
    }

    Serial.println(&date, "Today is %a, %d-%b-%Y");

    date.tm_year += 1900;
    date.tm_mon  += 1;

    return date;
}

/**
 * @brief checks if the given year is leap year
 * 
 * @param year 
 * @return true 
 * @return false 
 */
bool isLeapYear(int year)
{
    if (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0))
        return true;
    
    return false;
}

/**
 * @brief get the total days in a month
 * 
 * @param date 
 * @return int 
 */
int getDaysInMonth(struct tm *date)
{
    int days_in_month[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int year  = date->tm_year;
    int mon   = date->tm_mon;

    /* return the month days (other than Feb.)*/
    if (mon != 2)
        return days_in_month[(mon - 1) % 12];

    /* return Feb. month days depending on the year */
    if (isLeapYear(year))
        return 29;
    
    return 28;
}

/**
 * @brief get the lunar calendar for the given date
 * 
 * @param pDate 
 * @param pLunarDate 
 * @return ReturnStatus_t 
 */
ReturnStatus_t getLunarDate(struct tm *pDate, lunar_date_t *pLunarDate)
{
    ReturnStatus_t status = SUCCESS;

    lunar_date_t lunar_date;
    int year  = pDate->tm_year;
    int mon   = pDate->tm_mon;
    int mday  = pDate->tm_mday;

    String url = "https://v.juhe.cn/calendar/day?date=" + String(year) + "-" + String(mon) + "-" + String(mday) + "&key=" + JUHE_API_KEY;

    String payload = httpGetRqst(url);

    StaticJsonDocument<1024> doc;

    DeserializationError error = deserializeJson(doc, payload);
    if (error) 
    {
        Serial.print("deserializeJson() failed: ");
        Serial.println(error.c_str());
        status = UNSUCCESS;
    }

    strcpy(pLunarDate->animals_year, doc["result"]["data"]["animalsYear"]);
    strcpy(pLunarDate->lunar_year, doc["result"]["data"]["lunarYear"]);
    strcpy(pLunarDate->lunar_date, doc["result"]["data"]["lunar"]);
    strcpy(pLunarDate->holiday, doc["result"]["data"]["holiday"]);
    strcpy(pLunarDate->suit, doc["result"]["data"]["suit"]);
    strcpy(pLunarDate->avoid, doc["result"]["data"]["avoid"]);

    return status;
}