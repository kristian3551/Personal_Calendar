#include <iostream>
#include "String/String.h"
#include "Time.h"
#include "Date.h"
#include "Event.h"
#include "DaySchedule.h"
using namespace std;

// cd "f:\FMI resources\Summer semester\Object-oriented programming\Private-calendar\" ;
// if ($?) { g++ (Get-ChildItem -Recurse *.cpp) -o source } ; if ($?) { .\source }

int main() {
    Date date(1, 5, 2022);
    Time startTime(10, 0, 0);
    Time endTime(12, 0, 0);
    String name = "Some name";
    String comment = "Comment";
    Event event(name, comment, date, startTime, endTime);
    Event event1("Name2", "Some comment", date, Time(13, 00, 00), Time(15, 00, 00));
    DaySchedule schedule;
    schedule.addEvent(event);
    schedule.addEvent(event1);
    schedule.removeEvent(event1);
    cout << schedule.find(event);
}