#ifndef EVENT_H
#define EVENT_H
#include "String.h"
#include "Time.h"
#include "Date.h"

class Event {
    String name;
    String comment;
    Date date;
    Time startTime;
    Time endTime;
public:
    Event() = default;
    Event(const String& name, const String& comment, const Date& date, const Time& startTime,
        const Time& endTime);
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
};

#endif