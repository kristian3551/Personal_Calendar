#include "Time.h"
#include <iostream>

Time::Time(unsigned hours, unsigned minutes, unsigned seconds) {
    setHours(hours);
    setMinutes(minutes);
    setSeconds(seconds);
}
void Time::setHours(unsigned hours) {
    while(hours >= 24)
        hours -= 24;
    this->hours = hours;
}
void Time::setMinutes(unsigned minutes) {
    while(minutes >= 60) {
        minutes -= 60;
        setHours(hours + 1);
    }
    this->minutes = minutes;
}
void Time::setSeconds(unsigned seconds) {
    while(seconds >= 60) {
        seconds -= 60;
        setMinutes(minutes + 1);
    }
    this->seconds = seconds;
}

unsigned Time::getHours() const {
    return hours;
}
unsigned Time::getMinutes() const {
    return minutes;
}
unsigned Time::getSeconds() const {
    return seconds;
}

void Time::setTime(unsigned h, unsigned m, unsigned s) {
    setHours(h);
    setMinutes(m);
    setSeconds(s);
}

unsigned Time::convertInSeconds() const {
    return 3600 * hours + 60 * minutes + seconds;
}

bool Time::operator <(const Time& time) const {
    return convertInSeconds() < time.convertInSeconds();
}
bool Time::operator >(const Time& time) const {
    return convertInSeconds() > time.convertInSeconds();
}
bool Time::operator ==(const Time& time) const {
    return convertInSeconds() == time.convertInSeconds();
}

bool Time::operator <=(const Time& time) const {
    return (*this < time) || (*this == time);
}
bool Time::operator >=(const Time& time) const {
    return (*this > time) || (*this == time);
}

String Time::toString() const {
    return String(hours).concat(" ").concat(String(minutes))
        .concat(" ").concat(String(seconds));
}

void Time::print() const {
    std::cout << hours << ":" << minutes << ":" << seconds << " h";
}

Time Time::operator +(const Time& time) const {
    Time copy(*this);
    copy.setSeconds(copy.seconds + time.seconds);
    copy.setMinutes(copy.minutes + time.minutes);
    copy.setHours(copy.hours + time.hours);
    return copy;
}