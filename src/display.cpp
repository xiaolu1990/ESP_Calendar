#include "display.h"
#include "bitmap.h"
#include "weather.h"
#include "calendar.h"

extern ThinkInk_270_Tricolor_C44    epd;
extern U8G2_FOR_ADAFRUIT_GFX        u8g2;
extern struct tm date_today;
extern lunar_date_t lunar_date_today;
extern weather_t weather_today;
extern aqi_t     aqi_today;
extern locationID_t location;
extern bool battery_is_low;

const String dows[7]    = {"日", "一", "二", "三", "四", "五", "六"};
const String months[12] = {"一月", "二月", "三月", "四月", "五月", "六月", "七月", "八月", "九月", "十月", "十一月", "十二月"};

/**
 * @brief initialize the EPD
 * 
 */
void displayInit()
{
    epd.begin();
    u8g2.begin(epd);
    epd.clearBuffer();
    epd.setRotation(0);
}

/**
 * @brief display the main page information
 * 
 */
void displayMainPage()
{
    epd.powerUp();

    epd.clearBuffer();

    displayWeather();
    
    displayDate();
    
    displayMonthCalendar();
    
    if (battery_is_low)
        displayBattery();

    epd.display();

    epd.powerDown();
}

/**
 * @brief demo display on EPD
 * 
 */
void displayHello()
{
    epd.powerUp();;
    epd.clearBuffer();

    u8g2.setFont(u8g2_font_wqy12_t_gb2312);
    u8g2.drawUTF8(30, 30, "欢迎光临");
    
    epd.drawBitmap(100, 100, Bitmap_999_fill, ICON_SIZE, ICON_SIZE, EPD_BLACK);

    epd.display();

    epd.powerDown();
}

/**
 * @brief display F1 season games
 * 
 */
void displayF1Calendar()
{
    epd.powerUp();;
    epd.clearBuffer();

    epd.drawBitmap(SCREEN_WIDTH - 120, -20, Bitmap_f1_logo, 100, 100, EPD_RED);

    char text[30];
    int text_w;
    
    u8g2.setFont(u8g2_font_glasstown_nbp_tr); // 10x11
    // u8g2.setFont(u8g2_font_missingplanet_tr);   // 11x14
    
    /* Bahrain 05.03.2023 */
    sprintf(text, "%s", "Bahrain");
    u8g2.drawUTF8(10, 12, text);
    sprintf(text, "%s", "05.03");
    text_w = u8g2.getUTF8Width(text);
    u8g2.drawUTF8(120-text_w, 12, text);

    /* Saudi 19.03.2023 */
    sprintf(text, "%s", "Saudi");
    u8g2.drawUTF8(10, 24, text);
    sprintf(text, "%s", "19.03");
    text_w = u8g2.getUTF8Width(text);
    u8g2.drawUTF8(120-text_w, 24, text);

    /* Australian 02.04.2023 */
    sprintf(text, "%s", "Australian");
    u8g2.drawUTF8(10, 36, text);
    sprintf(text, "%s", "02.04");
    text_w = u8g2.getUTF8Width(text);
    u8g2.drawUTF8(120-text_w, 36, text);

    /* Azerbaijan 30.04.2023 */
    sprintf(text, "%s", "Azerbaijan");
    u8g2.drawUTF8(10, 48, text);
    sprintf(text, "%s", "30.04");
    text_w = u8g2.getUTF8Width(text);
    u8g2.drawUTF8(120-text_w, 48, text);

    /* Miami 07.05.2023 */
    sprintf(text, "%s", "Miami");
    u8g2.drawUTF8(10, 60, text);
    sprintf(text, "%s", "07.05");
    text_w = u8g2.getUTF8Width(text);
    u8g2.drawUTF8(120-text_w, 60, text);
    
    /* Emilia Romagna 21.05.2023 */
    sprintf(text, "%s", "Emilia");
    u8g2.drawUTF8(10, 72, text);
    sprintf(text, "%s", "21.05");
    text_w = u8g2.getUTF8Width(text);
    u8g2.drawUTF8(120-text_w, 72, text);

    /* Monaco 28.05.2023 */
    sprintf(text, "%s", "Monaco");
    u8g2.drawUTF8(10, 84, text);
    sprintf(text, "%s", "28.05");
    text_w = u8g2.getUTF8Width(text);
    u8g2.drawUTF8(120-text_w, 84, text);

    /* Spanish 04.06.2023 */
    sprintf(text, "%s", "Spain");
    u8g2.drawUTF8(10, 96, text);
    sprintf(text, "%s", "04.06");
    text_w = u8g2.getUTF8Width(text);
    u8g2.drawUTF8(120-text_w, 96, text);

    /* Canadian 18.06.2023 */
    sprintf(text, "%s", "Canada");
    u8g2.drawUTF8(10, 108, text);
    sprintf(text, "%s", "18.06");
    text_w = u8g2.getUTF8Width(text);
    u8g2.drawUTF8(120-text_w, 108, text);

    /* Austrian 02.07.2023 */
    sprintf(text, "%s", "Austrian");
    u8g2.drawUTF8(10, 120, text);
    sprintf(text, "%s", "02.07");
    text_w = u8g2.getUTF8Width(text);
    u8g2.drawUTF8(120-text_w, 120, text);

    /* British 09.07.2023 */
    sprintf(text, "%s", "Britain");
    u8g2.drawUTF8(10, 132, text);
    sprintf(text, "%s", "09.07");
    text_w = u8g2.getUTF8Width(text);
    u8g2.drawUTF8(120-text_w, 132, text);

    /* Hungarian 23.07.2023 */
    sprintf(text, "%s", "Hungary");
    u8g2.drawUTF8(10, 144, text);
    sprintf(text, "%s", "23.07");
    text_w = u8g2.getUTF8Width(text);
    u8g2.drawUTF8(120-text_w, 144, text);

    /* Belgian 30.07.2023 */
    sprintf(text, "%s", "Belgian");
    u8g2.drawUTF8(10, 156, text);
    sprintf(text, "%s", "30.07");
    text_w = u8g2.getUTF8Width(text);
    u8g2.drawUTF8(120-text_w, 156, text);

    /* Dutch 27.08.2023 */
    sprintf(text, "%s", "Dutch");
    u8g2.drawUTF8(10, 168, text);
    sprintf(text, "%s", "27.08");
    text_w = u8g2.getUTF8Width(text);
    u8g2.drawUTF8(120-text_w, 168, text);

    /* Italian 03.09.2023 */
    sprintf(text, "%s", "Italy");
    u8g2.drawUTF8(140, 72, text);
    sprintf(text, "%s", "03.09");
    text_w = u8g2.getUTF8Width(text);
    u8g2.drawUTF8(254-text_w, 72, text);

    /* Singapore 17.09.2023 */
    sprintf(text, "%s", "Singapore");
    u8g2.drawUTF8(140, 84, text);
    sprintf(text, "%s", "17.09");
    text_w = u8g2.getUTF8Width(text);
    u8g2.drawUTF8(254-text_w, 84, text);

    /* Japan 24.09.2023 */
    sprintf(text, "%s", "Japan");
    u8g2.drawUTF8(140, 96, text);
    sprintf(text, "%s", "24.09");
    text_w = u8g2.getUTF8Width(text);
    u8g2.drawUTF8(254-text_w, 96, text);

    /* Qatar 08.10.2023 */
    sprintf(text, "%s", "Qatar");
    u8g2.drawUTF8(140, 108, text);
    sprintf(text, "%s", "08.10");
    text_w = u8g2.getUTF8Width(text);
    u8g2.drawUTF8(254-text_w, 108, text);

    /* United States 22.10.2023 */
    sprintf(text, "%s", "United States");
    u8g2.drawUTF8(140, 120, text);
    sprintf(text, "%s", "22.10");
    text_w = u8g2.getUTF8Width(text);
    u8g2.drawUTF8(254-text_w, 120, text);

    /* Mexico 29.10.2023 */
    sprintf(text, "%s", "Mexico");
    u8g2.drawUTF8(140, 132, text);
    sprintf(text, "%s", "29.10");
    text_w = u8g2.getUTF8Width(text);
    u8g2.drawUTF8(254-text_w, 132, text);

    /* Brazilian 05.11.2023 */
    sprintf(text, "%s", "Brazil");
    u8g2.drawUTF8(140, 144, text);
    sprintf(text, "%s", "05.11");
    text_w = u8g2.getUTF8Width(text);
    u8g2.drawUTF8(254-text_w, 144, text);

    /* Las Vegas 19.11.2023 */
    sprintf(text, "%s", "Las Vegas");
    u8g2.drawUTF8(140, 156, text);
    sprintf(text, "%s", "19.11");
    text_w = u8g2.getUTF8Width(text);
    u8g2.drawUTF8(254-text_w, 156, text);

    /* Abu Dhabi 26.11.2023 */
    sprintf(text, "%s", "Abu Dhabi");
    u8g2.drawUTF8(140, 168, text);
    sprintf(text, "%s", "26.11");
    text_w = u8g2.getUTF8Width(text);
    u8g2.drawUTF8(254-text_w, 168, text);
    
    epd.display();

    epd.powerDown();
}

void displayWeather()
{
    char text[30];
    int text_w;
    unsigned char *icon = getWeatherIcon(weather_today.icon);

    epd.drawBitmap(10, 5, icon, ICON_SIZE, ICON_SIZE, EPD_BLACK);

    u8g2.setFont(u8g2_font_wqy12_t_gb2312);

    if (location == Shanghai)
    {
        sprintf(text, "%s", "上海");
        text_w = u8g2.getUTF8Width(text);
        u8g2.drawUTF8(15, 55, text);
    }

    sprintf(text, "%s", weather_today.text);
    text_w = u8g2.getUTF8Width(text);
    u8g2.drawUTF8(95-text_w, 55, text);

    sprintf(text, "AQI 指数: %s, %s", aqi_today.aqi, aqi_today.category);
    text_w = u8g2.getUTF8Width(text);
    u8g2.drawUTF8((100-text_w)/2, 70, text);

    // sprintf(text, "空气: %s", aqi_today.category);
    // text_w = u8g2.getUTF8Width(text);
    // u8g2.drawUTF8(95-text_w, 70, text);

    u8g2.setFont(u8g2_font_freedoomr25_tn);
    sprintf(text, "%s ", weather_today.temp);
    text_w = u8g2.getUTF8Width(text);
    u8g2.drawUTF8(95-text_w, 40, text);

    u8g2.setFont(u8g2_font_luBIS24_te);
    sprintf(text, "%s", "°");
    text_w = u8g2.getUTF8Width(text);
    u8g2.drawUTF8(95-text_w, 35, text);
}

/**
 * @brief display today's date information
 * 
 */
void displayDate()
{
    char text[30];
    int text_w;

    epd.drawFastHLine(5, 80, 90, EPD_BLACK);

    u8g2.setFont(u8g2_font_7Segments_26x42_mn);
    sprintf(text, "%d", date_today.tm_mday);
    text_w = u8g2.getUTF8Width(text);
    u8g2.drawUTF8((1+(98-text_w)/2), 150, text);
    
    u8g2.setFont(u8g2_font_wqy12_t_gb2312);
    sprintf(text, "%s", lunar_date_today.lunar_date);
    text_w = u8g2.getUTF8Width(text);
    u8g2.drawUTF8((1+(98-text_w)/2), 100, text);

    if (strlen(lunar_date_today.holiday) > 0)
    {
        sprintf(text, "%s", lunar_date_today.holiday);
        text_w = u8g2.getUTF8Width(text);
        u8g2.drawUTF8((1+(98-text_w)/2), 170, text);
    }

    /* display things suit and to avoid today, up to 4 */
    char *addr_suit, *addr_avoid;
    int cnt_suit = 0, cnt_avoid = 0;
    char str_suit[250], str_avoid[250];

    strcpy(str_suit, lunar_date_today.suit);
    addr_suit = strtok(str_suit, ".");
    u8g2.drawUTF8(104, 140, "宜: ");
    while(addr_suit != NULL)
    {
        if (cnt_suit > 3) break;

        sprintf(text, "%s ", addr_suit);
        text_w = u8g2.getUTF8Width(text);

        if (strlen(text) < 10)     // 3个汉字=10 byte
        {
            cnt_suit += 1;
            u8g2.drawUTF8(125 + (cnt_suit-1)*text_w, 140, text);
            // Serial.println(text);
        }
        
        addr_suit = strtok(NULL, ".");
    }

    strcpy(str_avoid, lunar_date_today.avoid);
    addr_avoid = strtok(str_avoid, ".");
    u8g2.drawUTF8(104, 160, "忌: ");
    while(addr_avoid != NULL)
    {
        if (cnt_avoid > 3) break;

        sprintf(text, "%s ", addr_avoid);
        text_w = u8g2.getUTF8Width(text);

        if (strlen(text) < 10)
        {
            cnt_avoid += 1;
            u8g2.drawUTF8(125 + (cnt_avoid-1)*text_w, 160, text);
            // Serial.println(text);
        }

        addr_avoid = strtok(NULL, ".");
    }
}

/**
 * @brief display the calendar month table
 * 
 */
void displayMonthCalendar()
{
    char text[30];
    int text_w, pos_x, pos_y;
    
    u8g2.setFont(u8g2_font_tenstamps_mf);
    sprintf(text, "%s", (String) date_today.tm_year);
    text_w = u8g2.getUTF8Width(text);
    u8g2.drawUTF8(100+(170-text_w)/2, 15, text);

    u8g2.setFont(u8g2_font_wqy12_t_gb2312);
    String month_zh = months[date_today.tm_mon-1];
    text_w = u8g2.getUTF8Width(month_zh.c_str());
    u8g2.drawUTF8(SCREEN_WIDTH-text_w-6, 15, month_zh.c_str());

    int day = date_today.tm_mday - date_today.tm_wday;
    String str_day = (String) day;
    int days_of_month = getDaysInMonth(&date_today);

    while (day > 1)
        day -= 7;

    pos_x = 0;
    pos_y = 36;
    for (int i=0; i<7; i++)
    {
        pos_x = 104 + i*(SCREEN_WIDTH-108)/7;
        text_w = u8g2.getUTF8Width(dows[i].c_str());
        u8g2.drawUTF8(pos_x+((SCREEN_WIDTH-100)/7-text_w)/2, pos_y, dows[i].c_str());
    }
        
    epd.drawLine(102, 40, 260, 40, EPD_BLACK);

    pos_y = 55;

    u8g2.setFont(u8g2_font_7x13B_mr);

    while(day <= days_of_month)
    {
        for (int i=0; i<7; i++)
        {
            pos_x = 104 + i*(SCREEN_WIDTH-108)/7;

            if ((day >= 1) && (day <= days_of_month))
            {
                text_w = u8g2.getUTF8Width(str_day.c_str());
                pos_x += (SCREEN_WIDTH-108)/7/2 - text_w/2;
                u8g2.setCursor(pos_x, pos_y);

                // highlight today with filled red circle
                if (day == date_today.tm_mday)
                {
                    int cur_x = u8g2.getCursorX();
                    int cur_y = u8g2.getCursorY();

                    u8g2.setBackgroundColor(EPD_RED);
                    u8g2.setForegroundColor(EPD_WHITE);

                    // epd.fillRoundRect(cur_x-2, cur_y-10, 14, 14, 2, EPD_RED);
                    epd.fillCircle(cur_x+6, cur_y-5, 7, EPD_RED);

                    u8g2.print(day);

                    u8g2.setBackgroundColor(EPD_WHITE);
                    u8g2.setForegroundColor(EPD_BLACK);
                }
                else
                {
                    u8g2.print(day);
                }
            }
            day++;
        }
        pos_y += 16;
    }
}

/**
 * @brief display battery status
 * 
 */
void displayBattery()
{
    u8g2.setFont(u8g2_font_battery19_tn);
    u8g2.drawGlyph(254, 172, 0x0031);
}