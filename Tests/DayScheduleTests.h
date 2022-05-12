#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"
#include "../DaySchedule/DaySchedule.h"

TEST_SUITE("DaySchedule class") {
    TEST_CASE("default constructor should work") {
        DaySchedule day;
        CHECK(day.getSize() == 0);
    }
    TEST_CASE("constructor should work") {
        DaySchedule day(Date(28, 4, 2022));
        CHECK(day.getDate().toString().equals("28 4 2022"));
        CHECK(day.getSize() == 0);
    }
    TEST_CASE("copy constructor should work") {
        DaySchedule day(Date(28, 4, 2022));
        DaySchedule day1 = day;
        CHECK(day1.getDate().toString().equals("28 4 2022"));
        CHECK(day1.getSize() == 0);
    }
    TEST_CASE("operator = should work") {
        DaySchedule day(Date(28, 4, 2022));
        DaySchedule day1;
        day1 = day;
        CHECK(day1.getDate().toString().equals("28 4 2022"));
        CHECK(day1.getSize() == 0);
    }
    TEST_CASE("add event should work") {
        DaySchedule day(Date(28, 4, 2022));
        Event event("Name", "Comment", 
            Date(28, 4, 2022), Time(10, 0, 0), Time(12, 0, 0));
        CHECK(day.addEvent(event));
        CHECK(day.getSize() == 1);
        CHECK(day.getEvents()[0]->getName().equals("Name"));
        Event event1("Name1", "Comment1", 
            Date(28, 4, 2022), Time(11, 0, 0), Time(13, 0, 0));
        CHECK_FALSE(day.addEvent(event1));
        Event event2("Name2", "Comment2", 
            Date(5, 5, 2022), Time(11, 0, 0), Time(13, 0, 0));
        CHECK_FALSE(day.addEvent(event2));
        Event event3("Name3", "Comment3", 
            Date(28, 4, 2022), Time(12, 0, 0), Time(13, 0, 0));
        CHECK(day.addEvent(event3));
        CHECK(day.getSize() == 2);
    }
    TEST_CASE("remove event should work") {
        DaySchedule day(Date(28, 4, 2022));
        Event event("Name", "Comment", 
            Date(28, 4, 2022), Time(10, 0, 0), Time(12, 0, 0));
        Event event1("Name1", "Comment1", 
            Date(28, 4, 2022), Time(10, 0, 0), Time(12, 0, 0));
        day.addEvent(event);
        CHECK(day.removeEvent(event1));
        CHECK_FALSE(day.removeEvent(event));
        CHECK(day.getSize() == 0);
    }
    TEST_CASE("find should work") {
        DaySchedule day(Date(28, 4, 2022));
        Event event("Name", "Comment", 
            Date(28, 4, 2022), Time(10, 0, 0), Time(12, 0, 0));
        day.addEvent(event);
        Event event1("Name1", "Comment1", 
            Date(28, 4, 2022), Time(10, 0, 0), Time(12, 0, 0));
        CHECK(day.find(event));
        CHECK_EQ(day.getEventIndex(event), 0);
        CHECK(day.find(event1));
    }
    TEST_CASE("findFreeTimeForEvent should work") {
        DaySchedule day(Date(28, 4, 2022));
        Event event("Name", "Comment", 
            Date(28, 4, 2022), Time(10, 0, 0), Time(12, 0, 0));
        day.addEvent(event);
        CHECK_EQ(day.findFreeTimeForEvent(Time(2, 0, 0)), Time(8, 0, 0));
        CHECK_EQ(day.findFreeTimeForEvent(Time(3, 0, 0)), Time(12, 0, 0));
        CHECK_EQ(day.findFreeTimeForEvent(Time(7, 0, 0)), Time(0, 0, 0));
    }
}