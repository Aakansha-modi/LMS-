//
//  Time.cpp
//  LMS
//
//  Created by Isha Sehrawat . on 28/06/23.
//

#include "Time.hpp"
#include <iostream>
#include <sstream>
#include <vector>
#include <string>


Time::Time() : Time(0,0,0){
}

Time::Time(int d, int m, int y){
    setDate(d);
    setMonth(m);
    setYear(y);
}

Time::Time(Time &t){
    this->setDate(t.date);
    this->setMonth(t.month);
    this->setYear(t.year);
}

Time::Time(std::string currentDate){
    std::vector<std::string> dateComponents;
    std::istringstream iss(currentDate);
    std::string token;
    while (std::getline(iss, token, '/')) {
        dateComponents.push_back(token);
    }
    // Extract day, month, and year from the split components
    int day = std::stoi(dateComponents[0]);
    int month = std::stoi(dateComponents[1]);
    int year = std::stoi(dateComponents[2]);
    Time(day,month,year);
}

Time::~Time(){}

int Time::getDays() const {
        int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30};
        int days = 0;
        for (int i = 1; i <getMonth(); ++i) {
            days += daysInMonth[i];
        }
        days += getDate();
        if (isLeapYear() and getMonth() > 2) {
            days += 1;
        }
        return days;
    }

int operator-(const Time &t1, const Time &t2){
    int tDays1 = t1.year * 365 + t1.year / 4 - t1.year / 100 + t1.year / 400 + t1.getDays();
    int tDays2 = t2.year * 365 + t2.year / 4 - t2.year / 100 + t2.year / 400 + t2.getDays();
    return std::abs(tDays1 - tDays2);
}
