#include "Calendar.h"
#include <iostream>
#include <fstream>
using namespace std;

const char* DATABASE_FILE_PATH = "database.dat";

void Calendar::resize() {
    capacity *= 2;
    DaySchedule** ptr = new DaySchedule*[capacity];
    for(int i = 0; i < size; i++) {
        ptr[i] = new DaySchedule(*days[i]);
    }
    free();
    days = ptr;
}
void Calendar::free() {
    for(int i = 0; i < size; i++)
        delete days[i];
    delete[] days;
}
void Calendar::copyFrom(const Calendar& calendar) {
    size = calendar.size;
    capacity = calendar.capacity;
    days = new DaySchedule*[capacity];
    for(int i = 0; i < size; i++)
        days[i] = new DaySchedule(*calendar.days[i]);
}

Calendar::Calendar() {
    readFromFile();
}
Calendar::Calendar(const Calendar& calendar) {
    copyFrom(calendar);
}
bool Calendar::addDay(const Date& date) {
    if(capacity == size) 
        resize();
    if(getDayIndexByDate(date) != -1) return false;
    int index = size;
    for(int i = 0; i < size; i++) {
        if(days[i]->getDate() > date) {
            index = i;
            break;
        }
    }
    for(int i = size; i > index; i--) {
        days[i] = days[i - 1];
    } 
    days[index] = new DaySchedule(date);
    size++;
    return true;
}
int binarySearch(const DaySchedule** days, int left, int right, const Date& date)
{
    if (right >= left) {
        int midIndex = left + (right - left) / 2;
        if (days[midIndex]->getDate() == date)
            return midIndex;
        if (days[midIndex]->getDate() > date)
            return binarySearch(days, left, midIndex - 1, date);
        return binarySearch(days, midIndex + 1, right, date);
    }
    return -1;
}
bool Calendar::addEvent(const Event& event) {
    int dayIndex = getDayIndexByDate(event.getDate());
    if(dayIndex == -1) 
        addDay(event.getDate());
    dayIndex = getDayIndexByDate(event.getDate());
    return days[dayIndex]->addEvent(event);
}
bool Calendar::removeEvent(const Event& event) {
    int dayIndex = getDayIndexByDate(event.getDate());
    if(dayIndex == -1) return false;
    for(int j = 0; j < days[dayIndex]->getSize(); j++) {
        if(*(days[dayIndex]->getEvents()[j]) == event) {
            return days[dayIndex]->removeEvent(event);
        }
    }
    return false;
}
void Calendar::printDay(const Date& date) const {
    int index = getDayIndexByDate(date);
    if(index == -1) {
        cout << "You have no arrangements for ";
        date.print();
        cout << endl;
        return;
    }
    for(int i = 0; i < days[index]->getSize(); i++) {
        cout << "---------" << endl;
        (*(days[index]->getEvents()[i])).print();
    }
}
void Calendar::printEventsByString(const String& str) const {
    for(int i = 0; i < size; i++) {
        const Event** dayEvents = days[i]->getEvents();
        for(int j = 0; j < days[i]->getSize(); j++) {
            
            if(dayEvents[j]->getName().contains(str) ||
            dayEvents[j]->getComment().contains(str)) 
                {
                    cout << "---------" << endl;
                    (*dayEvents[j]).print();
                }
        }
    }
}
bool Calendar::changeDate(const Event& event, const Date& date) {
    int eventDayIndex = getDayIndexByDate(event.getDate());
    if(eventDayIndex == -1) return false;
    int eventIndex = days[eventDayIndex]->getEventIndex(event);
    if(eventIndex == -1) return false;
    int dayIndex = getDayIndexByDate(date);
    if(dayIndex == -1) {
        addDay(date);
        dayIndex = getDayIndexByDate(date);
    }
    days[eventDayIndex]->removeEvent(event);
    Event copy(event);
    copy.setName(days[eventDayIndex]->getEvents()[eventIndex]->getName());
    copy.setComment(days[eventDayIndex]->getEvents()[eventIndex]->getComment());
    copy.setDate(date);
    return days[dayIndex]->addEvent(copy);
}
bool Calendar::changeName(const Event& event, const String& name) {
    int eventDayIndex = getDayIndexByDate(event.getDate());
    if(eventDayIndex == -1) return false;
    int eventIndex = days[eventDayIndex]->getEventIndex(event);
    if(eventIndex == -1) return false;
    days[eventDayIndex]->setNameByIndex(name, eventIndex);
    return true;
}
bool Calendar::changeComment(const Event& event, const String& comment) {
    int eventDayIndex = getDayIndexByDate(event.getDate());
    if(eventDayIndex == -1) return false;
    int eventIndex = days[eventDayIndex]->getEventIndex(event);
    if(eventIndex == -1) return false;
    days[eventDayIndex]->setCommentByIndex(comment, eventIndex);
    return true;
}
bool Calendar::changeStartTime(const Event& event, const Time& time) {
    int eventDayIndex = getDayIndexByDate(event.getDate());
    if(eventDayIndex == -1) return false;
    int eventIndex = days[eventDayIndex]->getEventIndex(event);
    if(eventIndex == -1) return false;
    Event copy(event);
    copy.setStartTime(time);
    copy.setName(days[eventDayIndex]->getEvents()[eventIndex]->getName());
    copy.setComment(days[eventDayIndex]->getEvents()[eventIndex]->getComment());
    days[eventDayIndex]->removeEvent(event);
    for(int i = 0; i < days[eventDayIndex]->getSize(); i++) {
        if(copy.doEventsIntersect(*days[eventDayIndex]->getEvents()[i])) {
            days[eventDayIndex]->addEvent(event);
            return false;
        }
    }
    return days[eventDayIndex]->addEvent(copy);
}
bool Calendar::changeEndTime(const Event& event, const Time& time) {
    int eventDayIndex = getDayIndexByDate(event.getDate());
    if(eventDayIndex == -1) return false;
    int eventIndex = days[eventDayIndex]->getEventIndex(event);
    if(eventIndex == -1) return false;
    Event copy(event);
    copy.setEndTime(time);
    copy.setName(days[eventDayIndex]->getEvents()[eventIndex]->getName());
    copy.setComment(days[eventDayIndex]->getEvents()[eventIndex]->getComment());
    days[eventDayIndex]->removeEvent(event);
    for(int i = 0; i < days[eventDayIndex]->getSize(); i++) {
        if(copy.doEventsIntersect(*days[eventDayIndex]->getEvents()[i])) {
            days[eventDayIndex]->addEvent(event);
            return false;
        }
    }
    return days[eventDayIndex]->addEvent(copy);
}
Calendar& Calendar::operator=(const Calendar& calendar) {
    if(this != &calendar) {
        free();
        copyFrom(calendar);
    }
    return *this;
}
int Calendar::getDayIndexByDate(const Date& date) const {
    return binarySearch((const DaySchedule**)days, 0, size - 1, date);
}

void Calendar::getStatsForPeriodInFile(const Date& date1, const Date& date2) {
    int countOfEvents[7] = {};
    for(int i = 0; i < size; i++) {
        if(((days[i]->getDate() >= date1) && (days[i]->getDate() <= date2)))
            countOfEvents[days[i]->getDate().getDayOfWeek()] += days[i]->getSize();
    }
    String filePath = String("stats-").concat(date1.getYear()).concat("-").concat(date1.getMonth())
        .concat("-").concat(date1.getDay()).concat(".txt");
    ofstream file(filePath.toString());
    for(int i = 0; i < 7; i++) {
        switch(i) {
            case 0: file << "Sunday: "; break;
            case 1: file << "Monday: "; break;
            case 2: file << "Tuesday: "; break;
            case 3: file << "Wednesday: "; break;
            case 4: file << "Thursday: "; break;
            case 5: file << "Friday: "; break;
            case 6: file << "Saturday: "; break;
        }
        file << countOfEvents[i] << " events" << endl;
    }
}

int Calendar::getCountOfEvents() const {
    int count = 0;
    for(int i = 0; i < size; i++) {
        count += days[i]->getSize();
    }
    return count;
}

void Calendar::saveInFile() const {
    ofstream file(DATABASE_FILE_PATH);
    file << size << endl;
    file << getCountOfEvents() << endl;
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < days[i]->getSize(); j++) {
            file << *(days[i]->getEvents()[j]) << endl;
        }
    }
}

void Calendar::readFromFile() {
    ifstream file(DATABASE_FILE_PATH);
    if(!file.is_open()) {
        capacity = 2;
        days = new DaySchedule*[capacity];
        size = 0;
        return;
    }
    int countOfDaysInFile = 0;
    file >> countOfDaysInFile;
    days = new DaySchedule*[countOfDaysInFile + 2];
    capacity = countOfDaysInFile + 2;
    size = 0;
    int countOfEventsInFile = 0;
    file >> countOfEventsInFile;
    for(int i = 0; i < countOfEventsInFile; i++) {
        int nameLength = 0;
        file >> nameLength;
        file.ignore();
        char* name = new char[nameLength + 1];
        file.getline(name, nameLength + 1);
        name[nameLength] = '\0';
        int commentLength = 0;
        file >> commentLength;
        file.ignore();
        char* comment = new char[commentLength + 1];
        file.getline(comment, commentLength + 1);
        comment[commentLength] = '\0';
        int day, month, year;
        file >> day >> month >> year;
        Date date(day, month, year);
        int hours, minutes, seconds;
        file >> hours >> minutes >> seconds;
        Time startTime(hours, minutes, seconds);
        file >> hours >> minutes >> seconds;
        Time endTime(hours, minutes, seconds);
        Event event(name, comment, date, startTime, endTime);
        addEvent(event);
        delete[] name, comment;
    }
}

void Calendar::findFreeTimeForEvent(const Date& date1, const Date& date2, const Time& time) const {
    if(date1 > date2) {
        cout << "Invalid period! Starting date should be less that ending date!" << endl;
        return;
    }
    for(Date d = date1; d <= date2; d.incrementDay()) {
        int dayIndex = getDayIndexByDate(d);
        if(dayIndex == -1) {
            cout << "Available date: ";
            d.print();
            cout << endl;
            cout << "The whole day is free!" << endl;
            return;
        }
        Time availableTime = days[dayIndex]->findFreeTimeForEvent(time);
        if(availableTime != Time()) {
            cout << "Available time: ";
            availableTime.print();
            cout << endl;
            return;
        }
    }
    cout << "There are no available hours this week!" << endl;
}

Calendar::~Calendar() {
    free();
} 