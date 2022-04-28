#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"
#include "../Date/Date.h"

TEST_SUITE("Date class") {
    TEST_CASE("default constructor should work") {
        Date date;
        CHECK_EQ(date.getDay(), 31);
        CHECK_EQ(date.getMonth(), 3);
        CHECK_EQ(date.getYear(), 1916);
    }
    TEST_CASE("constructor should work") {
        Date date(28, 4, 2022);
        CHECK_EQ(date.getDay(), 28);
        CHECK_EQ(date.getMonth(), 4);
        CHECK_EQ(date.getYear(), 2022);
    }
    TEST_CASE("day of week is calculated correctly") {
        Date d1(28, 4, 2022);
        Date d2(8, 6, 2022);
        CHECK_EQ(d1.getDayOfWeek(), 4);
        CHECK_EQ(d2.getDayOfWeek(), 3);
    }
    TEST_CASE("operators for comparison should work") {
        Date d1(28, 4, 2022);
        Date d2(8, 6, 2022);
        Date d3(8, 6, 2022);
        CHECK(d1 < d2);
        CHECK(d2 == d3);
        CHECK(d1 != d2);
        CHECK(d1 < d2);
        CHECK(d2 <= d3);
        CHECK(d2 >= d3);
    }
    TEST_CASE("is valid date should work") {
        CHECK(Date::isValidDate(28, 4, 2022));
        CHECK_FALSE(Date::isValidDate(32, 4, 2022));
        CHECK_FALSE(Date::isValidDate(29, 2, 2022));
        CHECK(Date::isValidDate(28, 2, 2022));
        CHECK_FALSE(Date::isValidDate(1, 2, 1));
        CHECK_FALSE(Date::isValidDate(12, 2, -1));
    }
    TEST_CASE("to string should work") {
        Date d1(28, 4, 2022);
        CHECK(d1.toString().equals("28 4 2022"));
    }
}