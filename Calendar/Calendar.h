#ifndef CALENDAR_H
#define CALENDAR_H
#include "../DaySchedule/DaySchedule.h"
#include "../Date/Date.h"
#include "../String/String.h"
#include "../Time/Time.h"
#include "../Event/Event.h"

class Calendar {
    DaySchedule* days;
    int size;
    int capacity;
    void resize();
    void free();
    void copyFrom(const Calendar&);
    int getDayIndexByDate(const Date&) const;
    bool addDay(const Date&);
    void readFromFile();
    int getCountOfEvents() const;
public:
    Calendar();
    Calendar(const Calendar&);
    bool addEvent(const Event&);
    bool removeEvent(const Event&);
    void printDay(const Date&) const;
    void printEventsByString(const String&) const;
    bool changeDate(const Event&, const Date&);
    bool changeName(const Event&, const String&);
    bool changeComment(const Event&, const String&);
    bool changeStartTime(const Event&, const Time&);
    bool changeEndTime(const Event&, const Time&);
    void getStatsForPeriodInFile(const Date&, const Date&);
    void findFreeTimeForEvent(const Date&, const Date&, const Time&) const;
    Calendar& operator=(const Calendar&);
    void saveInFile() const;
    ~Calendar();   
};

#endif