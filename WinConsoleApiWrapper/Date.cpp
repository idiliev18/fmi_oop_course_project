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

void Date::fromString(const std::string& dateStr)
{
    year = std::atoi(dateStr.substr(0, 4).c_str());
    month = std::atoi(dateStr.substr(5, 2).c_str());
    day = std::atoi(dateStr.substr(8, 2).c_str());
    hour = std::atoi(dateStr.substr(11, 2).c_str());
    minute = std::atoi(dateStr.substr(14, 2).c_str());
    second = std::atoi(dateStr.substr(17, 2).c_str());
}