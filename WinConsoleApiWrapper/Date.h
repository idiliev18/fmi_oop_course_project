#pragma once
#include <string>

class Date {
private:
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;

public:

    Date();
    void setToNow();
    std::string toString() const;
};