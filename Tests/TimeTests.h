#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"
#include "../Time/Time.h"

TEST_SUITE("Time class tests") {
    TEST_CASE("Constructors should work") {
        Time time;
        CHECK_EQ(time.getHours(), 0);
        CHECK_EQ(time.getMinutes(), 0);
        CHECK_EQ(time.getSeconds(), 0);
        Time time1(12, 30, 15);
        CHECK_EQ(time1.getHours(), 12);
        CHECK_EQ(time1.getMinutes(), 30);
        CHECK_EQ(time1.getSeconds(), 15);
    }
    TEST_CASE("setters should work") {
        Time time2(12, 62, 60);
        CHECK_EQ(time2.getHours(), 13);
        CHECK_EQ(time2.getMinutes(), 3);
        CHECK_EQ(time2.getSeconds(), 0);
        time2.setTime(8, 35, 40);
        CHECK_EQ(time2.getHours(), 8);
        CHECK_EQ(time2.getMinutes(), 35);
        CHECK_EQ(time2.getSeconds(), 40);
    }
    TEST_CASE("operators for comparison should work") {
        Time t1(12, 35, 40);
        Time t2(13, 1, 5);
        Time t3(13, 1, 5);
        CHECK((t1 < t2));
        CHECK((t2 > t1));
        CHECK(!(t1 == t2));
        CHECK(t2 == t3);
        CHECK((t1 <= t2));
        CHECK((t2 >= t1));
    }
    TEST_CASE("operator + should work") {
        Time t1(12, 35, 40);
        Time t2(4, 1, 5);
        Time t3 = t1 + t2;
        CHECK_EQ(t3.getHours(), 16);
        CHECK_EQ(t3.getMinutes(), 36);
        CHECK_EQ(t3.getSeconds(), 45);
    }
    TEST_CASE("toString should work") {
        Time t1(12, 35, 40);
        CHECK(t1.toString().equals("12 35 40"));
    }
}