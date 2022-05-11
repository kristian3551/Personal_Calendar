#include "Time.h"
#include <iomanip>
#include <iostream>

Time::Time(unsigned hours, unsigned minutes, unsigned seconds) {
    setHours(hours);
    setMinutes(minutes);
    setSeconds(seconds);
}
void Time::setHours(unsigned hours) {
    hours %= 24;
    this->hours = hours;
}
void Time::setMinutes(unsigned minutes) {
    setHours(hours + minutes / 60);
    this->minutes = minutes % 60;
}
void Time::setSeconds(unsigned seconds) {
    setMinutes(minutes + seconds / 60);
    this->seconds = seconds % 60;
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
    std::cout <<std::setfill('0') << std::setw(2) << hours << ":" << std::setfill('0') << std::setw(2) << minutes << ":" << std::setfill('0') << std::setw(2) << seconds << " h";
}

Time Time::operator +(const Time& time) const {
    Time copy(*this);
    copy.setSeconds(copy.seconds + time.seconds);
    copy.setMinutes(copy.minutes + time.minutes);
    copy.setHours(copy.hours + time.hours);
    return copy;
}

bool Time::operator !=(const Time& time) const {
    return !(*this == time);
}