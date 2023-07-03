//
//  Time.hpp
//  LMS
//
//  Created by Isha Sehrawat . on 28/06/23.
//

#ifndef Time_hpp
#define Time_hpp

#include <stdio.h>
#include <iostream>

class Time {
public:
    Time();
    Time(int d, int m, int y);
    // constructor to return Time object from given string dd/mm/yyyy
    Time(std::string);
    Time(Time &t);
    ~Time();

    
    // Getters
    int getDate() const {return date;}
    int getMonth() const {return month;}
    int getYear() const {return year;}
    
    // Setters
    void setDate(int d){date = d;}
    void setMonth(int m){month = m;}
    void setYear(int y){year = y;}
    
    
    // Funtcions
    int getDays() const;
    bool isLeapYear() const {return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);}
    
    // Operator Overloading
    friend int operator-(const Time &t1, const Time &t2);
    
private:
    int date{};
    int month{};
    int year{};
};

#endif /* Time_hpp */
