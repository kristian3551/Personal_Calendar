#include "Controller.h"
#include <iostream>
using namespace std;

const int MAX_NAME_LENGTH = 65;
const int MAX_COMMENT_LENGTH = 1024;
const int MAX_PROPERTY_LENGTH = 12;

void printDelimiter() {
    cout << "----------------------------------" << endl;
}

void Controller::addEvent() {
    cout << "You chose to add an event to your calendar" << endl;
    cout << "Enter name: ";
    char name[MAX_NAME_LENGTH];
    cin.getline(name, MAX_NAME_LENGTH);
    cout << "Enter comment: ";
    char comment[MAX_COMMENT_LENGTH];
    cin.getline(comment, MAX_COMMENT_LENGTH);
    cout << "Enter date (3 consequent numbers): ";
    int day, month, year;
    cin >> day >> month >> year;
    Date date(day, month, year);
    cout << "Enter start time (3 consequent numbers): ";
    int hours, minutes, seconds;
    cin >> hours >> minutes >> seconds;
    Time startTime(hours, minutes, seconds);
    cout << "Enter end time (3 consequent numbers): ";
    cin >> hours >> minutes >> seconds;
    Time endTime(hours, minutes, seconds);
    Event event(name, comment, date, startTime, endTime);
    bool res = calendar.addEvent(event);
    if(res) cout << "Successfully added event!" << endl;
    else cout << "There is an already saved event during that period of time!" << endl;
}

void Controller::removeEvent() {
    cout << "You chose to remove an event to your calendar!" << endl;
    cout << "Enter name: ";
    char name[MAX_NAME_LENGTH];
    cin.getline(name, MAX_NAME_LENGTH);
    cout << "Enter comment: ";
    char comment[MAX_COMMENT_LENGTH];
    cin.getline(comment, MAX_COMMENT_LENGTH);
    cout << "Enter date (3 consequent numbers): ";
    int day, month, year;
    cin >> day >> month >> year;
    Date date(day, month, year);
    cout << "Enter start time (3 consequent numbers): ";
    int hours, minutes, seconds;
    cin >> hours >> minutes >> seconds;
    Time startTime(hours, minutes, seconds);
    cout << "Enter end time (3 consequent numbers): ";
    cin >> hours >> minutes >> seconds;
    Time endTime(hours, minutes, seconds);
    Event event(name, comment, date, startTime, endTime);
    bool res = calendar.removeEvent(event);
    if(res) cout << "Successfully removed event!" << endl;
    else cout << "There is no such event in the database!" << endl;
}

void Controller::showDayEvents() {
    cout << "You chose to browse events on a specific day!" << endl;
    cout << "Enter date (3 consequent numbers): ";
    int day, month, year;
    cin >> day >> month >> year;
    Date date(day, month, year);
    printDelimiter();
    cout << "Events: " << endl;
    calendar.printDay(date);
}

void Controller::changeEvent() {
    cout << "You chose to change an event property! First you have to type the event details!" << endl;
    cout << "Enter name: ";
    char name[MAX_NAME_LENGTH];
    cin.getline(name, MAX_NAME_LENGTH);
    cout << "Enter comment: ";
    char comment[MAX_COMMENT_LENGTH];
    cin.getline(comment, MAX_COMMENT_LENGTH);
    cout << "Enter date (3 consequent numbers): ";
    int day, month, year;
    cin >> day >> month >> year;
    Date date(day, month, year);
    cout << "Enter start time (3 consequent numbers): ";
    int hours, minutes, seconds;
    cin >> hours >> minutes >> seconds;
    Time startTime(hours, minutes, seconds);
    cout << "Enter end time (3 consequent numbers): ";
    cin >> hours >> minutes >> seconds;
    Time endTime(hours, minutes, seconds);
    Event event(name, comment, date, startTime, endTime);
    printDelimiter();
    cout << "Enter type of property (name, comment, date, startTime, endTime): ";
    char property[MAX_PROPERTY_LENGTH];
    cin.ignore();
    cin.getline(property, MAX_PROPERTY_LENGTH);
    if(!strcmp(property, "name")) {
        cout << "Enter name: ";
        char newName[MAX_NAME_LENGTH];
        cin.getline(newName, MAX_NAME_LENGTH);
        bool res = calendar.changeName(event, newName);
        if(res) cout << "Successfully changed event name!" << endl;
        else cout << "Something went wrong!" << endl;
    }
    else if(!strcmp(property, "comment")) {
        cout << "Enter comment: ";
        char newComment[MAX_COMMENT_LENGTH];
        cin.getline(newComment, MAX_COMMENT_LENGTH);
        bool res = calendar.changeComment(event, newComment);
        if(res) cout << "Successfully changed event comment!" << endl;
        else cout << "Something went wrong!" << endl;
    }
    else if(!strcmp(property, "date")) {
        cout << "Enter date (3 consequent numbers): ";
        cin >> day >> month >> year;
        Date newDate(day, month, year);
        bool res = calendar.changeDate(event, newDate);
        if(res) cout << "Successfully changed event date!" << endl;
        else cout << "Something went wrong!" << endl;
    }
    else if(!strcmp(property, "startTime")) {
        cout << "Enter start time (3 consequent numbers): ";
        cin >> hours >> minutes >> seconds;
        Time newStartTime(hours, minutes, seconds);
        bool res = calendar.changeStartTime(event, newStartTime);
        if(res) cout << "Successfully changed event start time!" << endl;
        else cout << "Something went wrong!" << endl;
    }
    else if(!strcmp(property, "endTime")) {
        cout << "Enter end time (3 consequent numbers): ";
        cin >> hours >> minutes >> seconds;
        Time newEndTime(hours, minutes, seconds);
        bool res = calendar.changeEndTime(event, newEndTime);
        if(res) cout << "Successfully changed event end time!" << endl;
        else cout << "Something went wrong!" << endl;
    }
}

void Controller::getStatsForEmployment() {
    cout << "You chose to create a file for employment!" << endl;
    cout << "Enter starting date (3 consequent numbers): ";
    int day, month, year;
    cin >> day >> month >> year;
    Date date1(day, month, year);
    cout << "Enter ending date (3 consequent numbers): ";
    cin >> day >> month >> year;
    Date date2(day, month, year);
    calendar.getStatsForPeriodInFile(date1, date2);
    cout << "Successfully created file!" << endl;
}

void Controller::searchByString() {
    cout << "You chose to print all events containing a specific string!" << endl;
    cout << "Enter string: ";
    char substring[MAX_COMMENT_LENGTH];
    cin.getline(substring, MAX_COMMENT_LENGTH);
    printDelimiter();
    cout << "Events: " << endl;
    calendar.printEventsByString(substring); 
}

void Controller::findFreeTimeForEvent() {
    cout << "You chose to find a free hour for event!" << endl;
    cout << "Enter date (3 consequent numbers): ";
    int day, month, year;
    cin >> day >> month >> year;
    Date date(day, month, year);
    cout << "Enter time (3 consequent numbers): ";
    int hours, minutes, seconds;
    cin >> hours >> minutes >> seconds;
    Time time(hours, minutes, seconds);
    calendar.findFreeTimeForEvent(date, time);
}

void Controller::run() {
    cout << "Hello to my application!" << endl;
    cout << "You can switch between 7 commands. Type a number (between 1 and 7) to choose the command and type -1 to exit! Enjoy!" << endl;
    int command = 0;
    while(command != -1) {
        cout << "Enter command: ";
        cin >> command;
        cin.ignore();
        switch(command) {
            case 1: {
                addEvent();
            } break;
            case 2: {
                removeEvent();
            } break;
            case 3: {
                showDayEvents();
            } break;
            case 4: {
                changeEvent();
            } break;
            case 5: {
                searchByString();
            } break;
            case 6: {
                getStatsForEmployment();
            } break;
            case 7: {
                findFreeTimeForEvent();
            } break;
            default: command = -1;
        }
        printDelimiter();
    }
    cout << "Hope you enjoyed!";
}