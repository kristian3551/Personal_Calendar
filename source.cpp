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
    // Date date(1, 5, 2022);
    // Time startTime(10, 0, 0);
    // Time endTime(11, 0, 0);
    // Event event("Name1", "Comment1", date, startTime, endTime);
    // Event event1("Name2", "Some comment2", date, Time(13, 00, 00), Time(15, 0, 0));
    // Event event2("Name3", "Some comment3", Date(2, 5, 2022), startTime, endTime);
    // Event event3("Name4", "Some comment4", Date(3, 5, 2022), startTime, endTime);
    Calendar calendar;
    calendar.printEventsByString("");
}