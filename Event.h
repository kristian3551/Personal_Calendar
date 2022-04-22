#ifndef EVENT_H
#define EVENT_H
#include "String/String.h"
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
};

#endif