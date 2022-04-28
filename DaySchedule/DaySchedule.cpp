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
    if(capacity == size) 
        resize();
    for(int i = 0; i < size; i++) {
        if(event.doEventsIntersect(*events[i])) {
            return false;
        }
    }
    int index = size;
    for(int i = 0; i < size; i++) {
        if(event.getEndTime() <= (*events[i]).getStartTime()) {
            index = i;
            break;
        }
    }// 1 2, 3 4, 7 8
    
    for(int i = size; i > index; i--) {
        events[i] = events[i - 1];
    } 
    events[index] = new Event(event);
    size++;
    return true;
}
bool DaySchedule::removeEvent(const Event& event) {
    int index = -1;
    for(int i = 0; i < size; i++) {
        if(*events[i] == event) {
            index = i;
            break;
        }
    }
    if(index == -1) {
        return false;
    }
    for(int i = index + 1; i < size; i++) {
        events[i - 1] = events[i];
    }
    size--;
    return true;
}

bool DaySchedule::find(const Event& event) {
    for(int i = 0; i < size; i++) {
        if(*events[i] == event) return true;
    }
    return false;
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

bool DaySchedule::findFreeTimeForEvent(const Time& time) const {
    if(size == 0 || (time + WORK_TIME_START) <= events[0]->getStartTime()) {
        cout << "Available hour: ";
        WORK_TIME_START.print();
        cout << endl;
        return true;
    }
    if((events[size - 1]->getEndTime() + time) <= WORK_TIME_END) {
        cout << "Available hour: ";
        events[size - 1]->getEndTime().print();
        cout << endl;
        return true;
    }
    for(int i = 0; i < size - 1; i++) {
        if((events[i]->getEndTime() + time) <= events[i + 1]->getStartTime()) {
            cout << "Available hour: ";
            events[i]->getEndTime().print();
            cout << endl;
            return true;
        }
    }
    return false;
}

DaySchedule::~DaySchedule() {
    free();
}