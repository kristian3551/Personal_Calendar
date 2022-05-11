#include "DaySchedule.h"
#include <iostream>
using namespace std;

const Time WORK_TIME_START(8, 0, 0);
const Time WORK_TIME_END(18, 0, 0);

void DaySchedule::resize() {
    capacity *= 2;
    Event** ptr = new Event*[capacity];
    for(int i = 0; i < size; i++) {
        ptr[i] = new Event(*events[i]);
    }
    free();
    events = ptr;
}
void DaySchedule::free() {
    for(int i = 0; i < size; i++) 
        delete events[i];
    delete[] events;
}
void DaySchedule::copyFrom(const DaySchedule& schedule) {
    events = new Event*[schedule.capacity];
    for(int i = 0; i < schedule.size; i++) {
        events[i] = new Event(*schedule.events[i]);
    }
    size = schedule.size;
    capacity = schedule.capacity;
    date = schedule.date;
}

DaySchedule::DaySchedule() {
    capacity = 2;
    events = new Event*[capacity];
    size = 0;
}

DaySchedule::DaySchedule(const Date& date) {
    this->date = date;
    capacity = 2;
    events = new Event*[capacity];
    size = 0;
}
DaySchedule::DaySchedule(const DaySchedule& schedule) {
    copyFrom(schedule);
}
DaySchedule& DaySchedule::operator=(const DaySchedule& schedule) {
    if(this != &schedule) {
        free();
        copyFrom(schedule);
    }
    return *this;
}
bool DaySchedule::addEvent(const Event& event) {
    if(event.getDate() != date) return false;
    for(int i = 0; i < size; i++) {
        if(event.doEventsIntersect(*events[i])) {
            return false;
        }
    }
    if(capacity == size) 
        resize();
    int index = size;
    for(int i = 0; i < size; i++) {
        if(event.getEndTime() <= (*events[i]).getStartTime()) {
            index = i;
            break;
        }
    }
    
    for(int i = size; i > index; i--) {
        events[i] = events[i - 1];
    } 
    events[index] = new Event(event);
    size++;
    return true;
}
bool DaySchedule::removeEvent(const Event& event) {
    int index = getEventIndex(event);
    if(index == -1) {
        return false;
    }
    for(int i = index + 1; i < size; i++) {
        events[i - 1] = events[i];
    }
    size--;
    return true;
}

int binarySearch(const Event** events, int left, int right, const Event& event)
{
    if (right >= left) {
        int midIndex = left + (right - left) / 2;
        if (*events[midIndex] == event)
            return midIndex;
        if (events[midIndex]->getStartTime() > event.getStartTime())
            return binarySearch(events, left, midIndex - 1, event);
        return binarySearch(events, midIndex + 1, right, event);
    }
    return -1;
}

bool DaySchedule::find(const Event& event) const {
    return binarySearch((const Event**)events, 0, size - 1, event) != -1;
}
int DaySchedule::getEventIndex(const Event& event) const {
    return binarySearch((const Event**)events, 0, size - 1, event);
}
const Event** DaySchedule::getEvents() const {
    return (const Event**)events;
}
int DaySchedule::getSize() const {
    return size;
}

Date DaySchedule::getDate() const {
    return date;
}

Time DaySchedule::findFreeTimeForEvent(const Time& time) const {
    if(size == 0 || (time + WORK_TIME_START) <= events[0]->getStartTime()) {
        return WORK_TIME_START;
    }
    for(int i = 0; i < size - 1; i++) {
        if((events[i]->getEndTime() + time) <= events[i + 1]->getStartTime()) {
            return events[i]->getEndTime();
        }
    }
    if((events[size - 1]->getEndTime() + time) <= WORK_TIME_END) {
        return events[size - 1]->getEndTime();
    }
    return Time();
}

void DaySchedule::setNameByIndex(const String& name, int index) {
    if(index < 0 || index >= size) return;
    events[index]->setName(name);
}
void DaySchedule::setCommentByIndex(const String& comment, int index) {
    if(index < 0 || index >= size) return;
    events[index]->setComment(comment);
}
void DaySchedule::setStartTimeByIndex(const Time& startTime, int index) {
    if(index < 0 || index >= size) return;
    events[index]->setStartTime(startTime);
}
void DaySchedule::setEndTimeByIndex(const Time& endTime, int index) {
    if(index < 0 || index >= size) return;
    events[index]->setEndTime(endTime);
}

DaySchedule::~DaySchedule() {
    free();
}