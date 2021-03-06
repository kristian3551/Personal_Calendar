#ifndef TIME_H
#define TIME_H
#include "../String/String.h"

class Time {
    unsigned hours;
    unsigned minutes;
    unsigned seconds;
    unsigned convertInSeconds() const;
    void setHours(unsigned hours);
    void setMinutes(unsigned minutes);
    void setSeconds(unsigned seconds);
public:
    Time(unsigned hours = 0, unsigned minutes = 0, unsigned seconds = 0);
    void setTime(unsigned, unsigned, unsigned);
    unsigned getHours() const;
    unsigned getMinutes() const;
    unsigned getSeconds() const;
    bool operator <(const Time&) const;
    bool operator >(const Time&) const;
    bool operator <=(const Time&) const;
    bool operator >=(const Time&) const;
    bool operator ==(const Time&) const;
    bool operator !=(const Time&) const;
    Time operator +(const Time&) const;
    void print() const;
    String toString() const;
};

#endif