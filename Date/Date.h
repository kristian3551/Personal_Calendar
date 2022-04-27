#ifndef DATE_H
#define DATE_H
#include "../String/String.h"

class Date {
    unsigned day;
    unsigned month;
    unsigned year;
    unsigned dayOfWeek;
    unsigned daysInMonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    void setDayOfWeek();
    void fixChangeInCalendar();
    void setDay(unsigned day);
    void setMonth(unsigned month);
    void setYear(unsigned year);
public:
    Date();
    Date(unsigned day , unsigned month , unsigned year);
    Date(unsigned day, unsigned month, unsigned year, unsigned dayOfWeek);
    void incrementDay();
    unsigned getDay() const;
    unsigned getMonth() const;
    unsigned getYear() const;
    unsigned getDayOfWeek() const;
    bool operator ==(const Date&) const;
    bool operator !=(const Date&) const;
    bool operator <(const Date&) const;
    bool operator >(const Date&) const;
    bool operator <=(const Date&) const;
    bool operator >=(const Date&) const;
    String toString() const;
};

#endif