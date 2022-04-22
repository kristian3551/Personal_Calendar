#include "Date.h"

Date::Date(unsigned day, unsigned month, unsigned year) {
    setYear(year);
    setMonth(month);
    setDay(day);
    dayOfWeek = 5;
    setDayOfWeek();
}

Date::Date(unsigned day, unsigned month, unsigned year, unsigned dayOfWeek) {
    setYear(year);
    setMonth(month);
    setDay(day);
    this->dayOfWeek = dayOfWeek;
}

void Date::setDayOfWeek() {
    Date date(31, 3, 1916, 5);
    while(!(date == *this)) {
        date.incrementDay();
        this->dayOfWeek++;
        dayOfWeek %= 7;
    }
}

void Date::setDay(unsigned day) {
    if(day > daysInMonth[month - 1])
        day = 1;
    this->day = day;
    setDayOfWeek();
}
void Date::setMonth(unsigned month) {
    if(month > 12) month = 1;
    this->month = month;
    setDayOfWeek();
}
void Date::setYear(unsigned year) {
    this->year = year;
    if(year % 4 == 0 && year % 100 != 0) daysInMonth[1] = 29;
    else daysInMonth[1] = 28;
    setDayOfWeek();
}

void Date::incrementDay() {
    setDay(day + 1);
    if(day == 1) setMonth(month + 1);
    if(month == 1) setYear(year + 1);
}

unsigned Date::getDay() const {
    return day;
}
unsigned Date::getMonth() const {
    return month;
}
unsigned Date::getYear() const {
    return year;
}

unsigned Date::getDayOfWeek() const {
    return dayOfWeek;
}

bool Date::operator ==(const Date& date) const {
    return day == date.day && month == date.month && year == date.year;
}

bool Date::operator !=(const Date& date) const {
    return !(date == *this);
}

String Date::toString() const {
    return String(day).concat(" ").concat(String(month))
    .concat(" ").concat(String(year));
}