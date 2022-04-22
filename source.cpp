#include <iostream>
#include "String/String.h"
#include "Time.h"
#include "Date.h"
#include "Event.h"

using namespace std;

int main() {
    Date date(1, 5, 2022);
    Time startTime(10, 0, 0);
    Time endTime(12, 0, 0);
    String name = "Some name";
    String comment = "Comment";
    Event event(name, comment, date, startTime, endTime);
}