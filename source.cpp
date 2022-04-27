#include <iostream>
#include "String/String.h"
#include "Time.h"
#include "Date.h"
#include "Event.h"
#include "DaySchedule.h"
#include "Calendar.h"
using namespace std;

// cd "f:\FMI resources\Summer semester\Object-oriented programming\Private-calendar\" ;
// if ($?) { g++ (Get-ChildItem -Recurse *.cpp) -o source } ; if ($?) { .\source }

int main() {
    Date date(1, 5, 2022);
    Time startTime(10, 0, 0);
    Time endTime(11, 0, 0);
    String name = "Some name";
    String comment = "Comment";
    Event event(name, comment, date, startTime, endTime);
    Event event1("Name2", "Some comment", date, Time(13, 00, 00), Time(15, 0, 0));
    Calendar calendar;
    calendar.addEvent(event);
    calendar.addEvent(event1);
    cout << calendar.changeEndTime(event, Time(12, 30, 00));
    calendar.findEventsByString("");
}