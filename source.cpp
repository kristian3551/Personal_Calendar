#include <iostream>
// #include "Tests/DayScheduleTests.h"
// #include "Tests/CalendarTests.h"
// #include "Tests/DateTests.h"
// #include "Tests/EventTests.h"
// #include "Tests/TimeTests.h"
#include "Engine/Engine.h"
using namespace std;

// if ($?) { g++ (Get-ChildItem -Recurse *.cpp) -o source } ; if ($?) { .\source }

int main() {
    // doctest::Context c;
    // c.run();
    Engine engine;
    engine.run();
}