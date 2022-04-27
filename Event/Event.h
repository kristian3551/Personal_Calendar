#ifndef EVENT_H
#define EVENT_H
#include "../String/String.h"
#include "../Time/Time.h"
#include "../Date/Date.h"
#include <iostream>

class Event {
    String name;
    String comment;
    Date date;
    Time startTime;
    Time endTime;
public:
    Event() = default;
    Event(const String&, const String&, const Date&, const Time&,
        const Time&);
    String getName() const;
    String getComment() const;
    Date getDate() const;
    Time getStartTime() const;
    Time getEndTime() const;
    void setName(const String&);
    void setComment(const String&);
    void setDate(const Date&);
    void setStartTime(const Time&);
    void setEndTime(const Time&);
    bool operator ==(const Event&) const;
    bool doEventsIntersect(const Event&) const;
    void print() const;
    friend std::ostream& operator<<(std::ostream&, const Event&);
};

#endif