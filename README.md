# ESP_Calendar

## 简介 (Intro)
基于ESP32的墨水屏日历，提供天气，老黄历以及F1赛历等功能

主页显示：天气和空气指数信息，本月日历信息，当日农历及节假日信息，今日事宜

翻页显示：F1 2023 正赛日历

----

2.7'' E-ink display from [Adafruit](https://www.adafruit.com/product/4098) that shows the information of weather, month calendar, lunar calendar as well as F1 2023 season calendar. The whole kit was developed based on an ESP32.

Main page displays: month calendar, lunar calendar, weather and air quality, etc.

Press button to switch page display, which shows the F1 2023 Season Calendar.

## PCB设计文档 (PCB Design files)
https://oshwhub.com/zhangshunlu/esp_calendar

## 配置修改 (Configuration)
需在`main.h`文件中修改以下信息，其中`MY_CITY` 和 `MY_COUNTRY_CODE` 的值目前仅支持Shanghai和CN，其他城市和地区需修改相应代码

Edit the following part in the file `main.h`, note that the value of `MY_CITY` and `MY_COUNTRY_CODE` supports only for `Shanghai` and `CN` now, you will have to modify the corresponding functions in the source code to match your location.
```c
#define WIFI_SSID               "YOUR WIFI"
#define WIFI_PASSWORD           "YOUR WIFI PASSWORD"

#define QWEATHER_API_KEY        "YOUR API KEY"  // 和风天气API
#define MY_CITY                 "Shanghai"
#define MY_COUNTRY_CODE         "CN"

#define JUHE_API_KEY            "YOUR API KEY"  // 聚合数据API
```

## 实际效果 (Realistic view)
![image](https://user-images.githubusercontent.com/27411560/233379606-f2571505-afa2-466f-8786-9120ef67537a.png)
![image](https://user-images.githubusercontent.com/27411560/233378725-484a5d8b-4667-4cab-806c-7171c48d94b4.png)

