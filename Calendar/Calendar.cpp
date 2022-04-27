#include "Calendar.h"
#include <iostream>
#include <fstream>
using namespace std;

const char* DATABASE_FILE_PATH = "database.dat";

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
    readFromFile();
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
        
    return days[dayIndex].addEvent(event);
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
        cout << "---------" << endl;
        (*days[index].getEvents()[i]).print();
    }
}
void Calendar::printEventsByString(const String& str) const {
    for(int i = 0; i < size; i++) {
        const Event** dayEvents = days[i].getEvents();
        for(int j = 0; j < days[i].getSize(); j++) {
            
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

void Calendar::getStatsForPeriodInFile(const Date& date1, const Date& date2) {
    int countOfEvents[7] = {};
    for(int i = 0; i < size; i++) {
        if(((days[i].getDate() >= date1) && (days[i].getDate() <= date2)))
            countOfEvents[days[i].getDate().getDayOfWeek()] += days[i].getSize();
    }
    String filePath = String().concat(date1.getYear()).concat("-").concat(date1.getMonth())
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
        for(int j = 0; j < days[i].getSize(); j++) {
            count++;
        }
    }
    return count;
}

void Calendar::saveInFile() const {
    ofstream file(DATABASE_FILE_PATH);
    file << size << endl;
    file << getCountOfEvents() << endl;
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < days[i].getSize(); j++) {
            file << *(days[i].getEvents()[j]) << endl;
        }
    }
}

void Calendar::readFromFile() {
    ifstream file(DATABASE_FILE_PATH);
    if(!file.is_open()) return;
    int countOfDaysInFile = 0;
    file >> countOfDaysInFile;
    days = new DaySchedule[countOfDaysInFile + 2];
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

void Calendar::findFreeTimeForEvent(const Date& date, const Time& time) const {
    int dayIndex = getDayIndexByDate(date);
    if(dayIndex == -1) {
        cout << "The whole day is free!" << endl;
        return;
    }
    days[dayIndex].findFreeTimeForEvent(time);
}

Calendar::~Calendar() {
    saveInFile();
    free();
} 