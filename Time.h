#ifndef TIME_H
#define TIME_H
#include "String.h"

class Time {
    unsigned hours;
    unsigned minutes;
    unsigned seconds;
    unsigned convertInSeconds() const;
    void setHours(unsigned hours);
    void setMinutes(unsigned minutes);
    void setSeconds(unsigned seconds);
public:
    Time() = default;
    Time(unsigned hours, unsigned minutes, unsigned seconds);
    void setTime(unsigned, unsigned, unsigned);
    unsigned getHours() const;
    unsigned getMinutes() const;
    unsigned getSeconds() const;
    bool operator <(const Time&) const;
    bool operator >(const Time&) const;
    bool operator ==(const Time&) const;
    String toString() const;
};

#endif