#include "DaySchedule.h"

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
    delete[] events;
}
void DaySchedule::copyFrom(const DaySchedule& schedule) {
    events = new Event*[schedule.capacity];
    for(int i = 0; i < schedule.size; i++) {
        events[i] = new Event(*schedule.events[i]);
    }
    size = schedule.size;
    capacity = schedule.capacity;
}

DaySchedule::DaySchedule() {
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
    if(capacity == size) 
        resize();
    for(int i = 0; i < size; i++) {
        if(!((*events[i]).getEndTime() < event.getStartTime() || (*events[i]).getStartTime() > event.getEndTime())) {
            // send message
            return false;
        }
    }
    events[size++] = new Event(event);
    return true;
}
bool DaySchedule::removeEvent(const Event& event) {
    int index = -1;
    for(int i = 0; i < size; i++) {
        if((*events[i]).getName().equals(event.getName())) {
            index = i;
            break;
        }
    }
    if(index == -1) {
        // send message
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
        if((*events[i]).getName().equals(event.getName())) return true;
    }
    return false;
}
const Event** DaySchedule::getEvents() const {
    return (const Event**)events;
}
int DaySchedule::getSize() const {
    return size;
}
DaySchedule::~DaySchedule() {
    free();
}