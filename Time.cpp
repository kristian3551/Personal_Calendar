#include "Time.h"

Time::Time(unsigned hours, unsigned minutes, unsigned seconds) {
    setHours(hours);
}
void Time::setHours(unsigned hours) {
    if(hours > 24)
        hours = 0;
    this->hours = hours;
}
void Time::setMinutes(unsigned minutes) {
    if(minutes > 60) minutes = 0;
    this->minutes = minutes;
}
void Time::setSeconds(unsigned seconds) {
    if(seconds > 60) seconds = 0;
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