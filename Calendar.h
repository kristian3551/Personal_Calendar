#ifndef CALENDAR_H
#define CALENDAR_H
#include "DaySchedule.h"
#include "Date.h"
#include "String.h"
#include "Time.h"
#include "Event.h"

class Calendar {
    DaySchedule* days;
    int size;
    int capacity;
    void resize();
    void free();
    void copyFrom(const Calendar&);
    int getDayIndexByDate(const Date&) const;
    bool addDay(const Date&);
public:
    Calendar();
    Calendar(const Calendar&);
    bool addEvent(const Event&);
    bool removeEvent(const Event&);
    void printDay(const Date&) const;
    void findEventsByString(const String&) const;
    bool changeDate(const Event&, const Date&);
    bool changeName(const Event&, const String&);
    bool changeComment(const Event&, const String&);
    bool changeStartTime(const Event&, const Time&);
    bool changeEndTime(const Event&, const Time&);
    Calendar& operator=(const Calendar&);
    ~Calendar();   
};

#endif