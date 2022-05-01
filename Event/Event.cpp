#include "Event.h"
#include <iostream>
using namespace std;

Event::Event(const String& name, const String& comment, const Date& date,
        const Time& startTime,
        const Time& endTime) {
            setName(name);
            setComment(comment);
            setDate(date);
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
    if(time > endTime) {
        startTime = endTime;
        endTime = time;
    }
    else startTime = time;
}
void Event::setEndTime(const Time& time) {
    if(time < startTime) {
        endTime = startTime;
        startTime = time;
    }
    else endTime = time;
}

bool Event::operator ==(const Event& event) const {
    return name.equals(event.name) && comment.equals(event.comment)
        && (date == event.date) && (startTime == event.startTime) && (endTime == event.endTime);
}

ostream& operator<<(ostream& os, const Event& event) {
    os << event.name.getLength() << " " << event.name << endl 
        << event.comment.getLength() << " " <<  event.comment << endl << event.date.toString()
    << endl << event.startTime.toString() << endl << event.endTime.toString();
    return os;
}

bool Event::doEventsIntersect(const Event& event) const {
    // if(date != event.getDate()) return false;
    if(endTime <= event.startTime) return false;
    if(startTime >= event.endTime) return false;
    return true;
}

void Event::print() const {
    cout << "Name: " << name << endl;
    cout << "Comment: " << comment << endl;
    cout << "Date: ";
    date.print();
    cout << endl;
    cout << "From ";
    startTime.print();
    cout << " to ";
    endTime.print();
    cout << endl;
}