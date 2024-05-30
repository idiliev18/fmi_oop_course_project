#include "Date.h"
#include <ctime>

Date::Date() 
{
    setToNow();
}

void Date::setToNow() 
{
    std::time_t now = std::time(0);
    std::tm ltm;
    localtime_s(&ltm, &now);
    year = 1900 + ltm.tm_year;
    month = 1 + ltm.tm_mon;
    day = ltm.tm_mday;
    hour = ltm.tm_hour;
    minute = ltm.tm_min;
    second = ltm.tm_sec;
}


std::string Date::toString() const 
{
    std::string result;
    result += std::to_string(year) + "-";
    result += (month < 10 ? "0" : "") + std::to_string(month) + "-";
    result += (day < 10 ? "0" : "") + std::to_string(day) + " ";
    result += (hour < 10 ? "0" : "") + std::to_string(hour) + ":";
    result += (minute < 10 ? "0" : "") + std::to_string(minute) + ":";
    result += (second < 10 ? "0" : "") + std::to_string(second);
    return result;
}