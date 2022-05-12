#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"
#include "../Event/Event.h"

TEST_SUITE("Event class") {
    TEST_CASE("constructor should work") {
        Event event("Name", "Comment", 
            Date(28, 4, 2022), Time(10, 0, 0), Time(12, 0, 0));
        CHECK(event.getName().equals("Name"));
        CHECK(event.getComment().equals("Comment"));
        CHECK(event.getDate().toString().equals("28 4 2022"));
        CHECK(event.getStartTime().toString().equals("10 0 0"));
        CHECK(event.getEndTime().toString().equals("12 0 0"));
    }
    TEST_CASE("setters should work") {
        Event event("Name", "Comment", 
            Date(28, 4, 2022), Time(10, 0, 0), Time(12, 0, 0));
        event.setName("NewName");
        CHECK(event.getName().equals("NewName"));
        event.setComment("NewComment");
        CHECK(event.getComment().equals("NewComment"));
        event.setDate(Date(5, 5, 2022));
        CHECK(event.getDate().toString().equals("5 5 2022"));
        event.setStartTime(Time(9, 30, 0));
        CHECK(event.getStartTime().toString().equals("9 30 0"));
        event.setEndTime(Time(19, 20, 5));
        CHECK(event.getEndTime().toString().equals("19 20 5"));
    }
    TEST_CASE("operator == should work") {
        Event event("Name", "Comment", 
            Date(28, 4, 2022), Time(10, 0, 0), Time(12, 0, 0));
        Event event1("Name", "Comment", 
            Date(28, 4, 2022), Time(10, 0, 0), Time(12, 0, 0));
        CHECK(event1 == event);
        Event event2("Name1", "Comment", 
            Date(28, 4, 2022), Time(10, 0, 0), Time(12, 0, 0));
        CHECK(event2 == event);
        Event event3("Name", "Comment", 
            Date(29, 4, 2022), Time(11, 0, 0), Time(12, 0, 0));
        CHECK_FALSE(event3 == event);
    }
    TEST_CASE("intersect check should work") {
        Event event("Name", "Comment", 
            Date(28, 4, 2022), Time(10, 0, 0), Time(12, 0, 0));
        Event event1("Name1", "Comment1", 
            Date(28, 4, 2022), Time(11, 0, 0), Time(13, 0, 0));
        CHECK(event.doEventsIntersect(event1));
        Event event2("Name2", "Comment2", 
            Date(28, 4, 2022), Time(9, 0, 0), Time(13, 0, 0));
        CHECK(event.doEventsIntersect(event2));
    }
}