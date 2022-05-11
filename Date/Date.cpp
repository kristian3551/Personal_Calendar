#include "Date.h"
#include <iostream>
#include <iomanip>
using namespace std;

Date::Date() {
    day = 31;
    month = 3;
    year = 1916;
    dayOfWeek = 5;
}

Date::Date(unsigned day, unsigned month, unsigned year) {
    if(Date(day, month, year, 0) < Date(31, 3, 1916, 5)) {
        day = 31;
        month = 3;
        year = 1916;
    }
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
    while(date != *this) {
        date.incrementDay();
        this->dayOfWeek++;
    }
    this->dayOfWeek %= 7;
}

void Date::setDay(unsigned day) {
    if(day > daysInMonth[month - 1])
        day = 1;
    this->day = day;
}
void Date::setMonth(unsigned month) {
    if(month > 12) month = 1;
    this->month = month;
    
}
void Date::setYear(unsigned year) {
    this->year = year;
    if(year % 4 == 0 && year % 100 != 0 || year % 400 == 0) daysInMonth[1] = 29;
    else daysInMonth[1] = 28;
    
}

void Date::incrementDay() {
    setDay(day + 1);
    if(day == 1) {
        setMonth(month + 1);
        if(month == 1) setYear(year + 1);
    }
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

bool Date::operator <(const Date& date) const {
    if(year < date.year) return true;
    if(year == date.year && month < date.month) return true;
    if(year == date.year && month == date.month
        && day < date.day) return true;
    return false;
}
bool Date::operator >(const Date& date) const {
    return !(*this < date) && *this != date;
}
bool Date::operator <=(const Date& date) const {
    return (*this < date) || (*this == date);
}
bool Date::operator >=(const Date& date) const {
    return (*this > date) || (*this == date);
}

String Date::toString() const {
    return String(day).concat(" ").concat(String(month))
    .concat(" ").concat(String(year));
}

bool Date::isValidDate(int day, int month, int year) {
    if(month <= 0 || month > 12) return false;
    if(year <= 0) return false;
    unsigned daysInMonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if(year % 4 == 0 && year % 100 != 0 || year % 400 == 0) daysInMonth[1] = 29;
    else daysInMonth[1] = 28;
    if(day < 0 || day > daysInMonth[month - 1]) return false;
    return (Date(day, month, year, 5) >= Date(31, 3, 1916, 5));
}

void Date::print() const {
   cout << setfill('0') << setw(2) << day << "/" << setfill('0') << setw(2) << month << "/" << year << " Day: ";
   switch(this->dayOfWeek) {
        case 0: cout << "Sunday"; break;
        case 1: cout << "Monday"; break;
        case 2: cout << "Tuesday"; break;
        case 3: cout << "Wednesday"; break;
        case 4: cout << "Thursday"; break;
        case 5: cout << "Friday"; break;
        case 6: cout << "Saturday"; break;
    }
}