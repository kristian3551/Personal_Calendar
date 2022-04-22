#include "Event.h"

Event::Event(const String& name, const String& comment, const Date& date, const Time& startTime,
        const Time& endTime) {
            this->name = name;
            this->comment = comment;
            this->date = date;
            this->startTime = startTime;
            this->endTime = endTime;
        }
String Event::getName() const {
    return name;
}
String Event::getComment() const {
    return comment;
}
Date Event::getDate() const {
    return date;
}
Time Event::getStartTime() const {
    return startTime;
}
Time Event::getEndTime() const {
    return endTime;
}
void Event::setName(const String& name) {
    this->name = name;
}
void Event::setComment(const String& comment) {
    this->comment = comment;
}
void Event::setDate(const Date& date) {
    this->date = date;
}
void Event::setStartTime(const Time& time) {
    startTime = time;
}
void Event::setEndTime(const Time& time) {
    endTime = time;
}