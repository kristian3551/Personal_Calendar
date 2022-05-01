#ifndef SCHEDULE_H
#define SCHEDULE_H
#include "../Event/Event.h"
#include "../Date/Date.h"

class DaySchedule {
    Date date;
    Event** events;
    int size;
    int capacity;
    void resize();
    void free();
    void copyFrom(const DaySchedule&);
public:
    DaySchedule();
    DaySchedule(const Date&);
    DaySchedule(const DaySchedule&);
    DaySchedule& operator=(const DaySchedule&);
    bool addEvent(const Event&);
    bool removeEvent(const Event&);
    bool find(const Event&);
    const Event** getEvents() const;
    int getSize() const;
    Date getDate() const;
    Time findFreeTimeForEvent(const Time&) const;
    ~DaySchedule();
};

#endif