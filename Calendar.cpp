#include "Calendar.h"
#include <iostream>
using namespace std;

void Calendar::resize() {
    capacity *= 2;
    DaySchedule* ptr = new DaySchedule[capacity];
    for(int i = 0; i < size; i++) {
        ptr[i] = days[i];
    }
    free();
    days = ptr;
}
void Calendar::free() {
    delete[] days;
}
void Calendar::copyFrom(const Calendar& calendar) {
    size = calendar.size;
    capacity = calendar.capacity;
    days = new DaySchedule[capacity];
    for(int i = 0; i < size; i++)
        days[i] = calendar.days[i];
}

Calendar::Calendar() {
    capacity = 2;
    days = new DaySchedule[capacity];
    size = 0;
}
Calendar::Calendar(const Calendar& calendar) {
    copyFrom(calendar);
}
bool Calendar::addDay(const Date& date) {
    if(capacity == size) 
        resize();
    for(int i = 0; i < size; i++) {
        if(days[i].getDate() == date) 
            return false;
    }
    days[size++] = DaySchedule(date);
    return true;
}
bool Calendar::addEvent(const Event& event) {
    int dayIndex = size;
    for(int i = 0; i < size; i++) {
        if(days[i].getDate() == event.getDate()) {
            dayIndex = i;
            break;
        }
    }
    if(dayIndex == size) 
        addDay(event.getDate());
    return days[size - 1].addEvent(event);
}
bool Calendar::removeEvent(const Event& event) {
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < days[i].getSize(); j++) {
            if(*(days[i].getEvents()[j]) == event) {
                return days[i].removeEvent(event);
            }
        }
    }
    return false;
}
void Calendar::printDay(const Date& date) const {
    int index = -1;
    for(int i = 0; i < size; i++) {
        if(days[i].getDate() == date) {
            index = i;
            break;
        }
    }
    if(index == -1) {
        cout << "You have no arrangements for " << date.toString() << endl;
        return;
    }
    for(int i = 0; i < days[index].getSize(); i++) {
        cout << *days[index].getEvents()[i] << endl;
    }
}
void Calendar::findEventsByString(const String& str) const {
    for(int i = 0; i < size; i++) {
        const Event** dayEvents = days[i].getEvents();
        for(int j = 0; j < days[i].getSize(); j++) {
            if(dayEvents[j]->getName().contains(str) ||
            dayEvents[j]->getComment().contains(str)) 
                cout << *dayEvents[j] << endl;
        }
    }
}
bool Calendar::changeDate(const Event& event, const Date& date) {
    int eventDayIndex = getDayIndexByDate(event.getDate());
    if(eventDayIndex == -1) return false;
    int eventIndex = -1;
    for(int i = 0; i < days[eventDayIndex].getSize(); i++) {
        if(*days[eventDayIndex].getEvents()[i] == event) {
            eventIndex = i;
            break;
        }
    }
    if(eventIndex == -1) return false;
    int dayIndex = getDayIndexByDate(date);
    if(dayIndex == -1) {
        addDay(date);
        dayIndex = size - 1;
    }
    days[eventDayIndex].removeEvent(event);
    Event copy(event);
    copy.setDate(date);
    return days[dayIndex].addEvent(copy);
}
bool Calendar::changeName(const Event& event, const String& name) {
    int eventDayIndex = getDayIndexByDate(event.getDate());
    if(eventDayIndex == -1) return false;
    int eventIndex = -1;
    for(int i = 0; i < days[eventDayIndex].getSize(); i++) {
        if(*days[eventDayIndex].getEvents()[i] == event) {
            eventIndex = i;
            break;
        }
    }
    if(eventIndex == -1) return false;
    days[eventDayIndex].removeEvent(event);
    Event copy(event);
    copy.setName(name);
    return days[eventDayIndex].addEvent(copy);
}
bool Calendar::changeComment(const Event& event, const String& comment) {
    int eventDayIndex = getDayIndexByDate(event.getDate());
    if(eventDayIndex == -1) return false;
    int eventIndex = -1;
    for(int i = 0; i < days[eventDayIndex].getSize(); i++) {
        if(*days[eventDayIndex].getEvents()[i] == event) {
            eventIndex = i;
            break;
        }
    }
    if(eventIndex == -1) return false;
    days[eventDayIndex].removeEvent(event);
    Event copy(event);
    copy.setName(comment);
    return days[eventDayIndex].addEvent(copy);
}
bool Calendar::changeStartTime(const Event& event, const Time& time) {
    int eventDayIndex = getDayIndexByDate(event.getDate());
    if(eventDayIndex == -1) return false;
    int eventIndex = -1;
    for(int i = 0; i < days[eventDayIndex].getSize(); i++) {
        if(*days[eventDayIndex].getEvents()[i] == event) {
            eventIndex = i;
            break;
        }
    }
    if(eventIndex == -1) return false;
    Event copy(event);
    copy.setStartTime(time);
    days[eventDayIndex].removeEvent(event);
    for(int i = 0; i < days[eventDayIndex].getSize(); i++) {
        if(copy.doEventsIntersect(*days[eventDayIndex].getEvents()[i])) {
            days[eventDayIndex].addEvent(event);
            return false;
        }
    }
    days[eventDayIndex].removeEvent(event);
    return days[eventDayIndex].addEvent(copy);
}
bool Calendar::changeEndTime(const Event& event, const Time& time) {
    int eventDayIndex = getDayIndexByDate(event.getDate());
    if(eventDayIndex == -1) return false;
    int eventIndex = -1;
    for(int i = 0; i < days[eventDayIndex].getSize(); i++) {
        if(*days[eventDayIndex].getEvents()[i] == event) {
            eventIndex = i;
            break;
        }
    }
    if(eventIndex == -1) return false;
    Event copy(event);
    copy.setEndTime(time);
    days[eventDayIndex].removeEvent(event);
    for(int i = 0; i < days[eventDayIndex].getSize(); i++) {
        if(copy.doEventsIntersect(*days[eventDayIndex].getEvents()[i])) {
            days[eventDayIndex].addEvent(event);
            return false;
        }
    }
    days[eventDayIndex].removeEvent(event);
    return days[eventDayIndex].addEvent(copy);
}
Calendar& Calendar::operator=(const Calendar& calendar) {
    if(this != &calendar) {
        free();
        copyFrom(calendar);
    }
    return *this;
}
int Calendar::getDayIndexByDate(const Date& date) const {
    for(int i = 0; i < size; i++) {
        if(days[i].getDate() == date) return i;
    }
    return -1;
}

Calendar::~Calendar() {
    free();
} 