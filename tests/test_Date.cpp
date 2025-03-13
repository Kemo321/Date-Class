#include <gtest/gtest.h>
#include "Date.hpp"
#include <sstream>

class DateTest : public ::testing::Test {
protected:
    void SetUp() override {
    }
};

// Constructor Tests
TEST(DateTest, ConstructorValid) {
    Date d(1, 1, 2024);
    EXPECT_EQ(d.get_day(), 1);
    EXPECT_EQ(d.get_month(), 1);
    EXPECT_EQ(d.get_year(), 2024);

    // Test leap year
    Date d2(29, 2, 2024);
    EXPECT_EQ(d2.get_day(), 29);
    EXPECT_EQ(d2.get_month(), 2);
    EXPECT_EQ(d2.get_year(), 2024);

    // Test maximum day in a month
    Date d3(31, 12, 2023);
    EXPECT_EQ(d3.get_day(), 31);
    EXPECT_EQ(d3.get_month(), 12);
    EXPECT_EQ(d3.get_year(), 2023);
}

TEST(DateTest, ConstructorInvalidDay) {
    EXPECT_THROW(Date(0, 1, 2024), std::invalid_argument);  // Day < 1
    EXPECT_THROW(Date(32, 1, 2024), std::invalid_argument); // Day > 31 for January
    EXPECT_THROW(Date(29, 2, 2023), std::invalid_argument); // Non-leap year
    EXPECT_THROW(Date(30, 2, 2024), std::invalid_argument); // February in leap year
    EXPECT_THROW(Date(31, 4, 2024), std::invalid_argument); // April has 30 days
}

TEST(DateTest, ConstructorInvalidMonth) {
    EXPECT_THROW(Date(1, 0, 2024), std::invalid_argument);  // Month < 1
    EXPECT_THROW(Date(1, 13, 2024), std::invalid_argument); // Month > 12
}

TEST(DateTest, ConstructorInvalidYear) {
    EXPECT_THROW(Date(1, 1, -1), std::invalid_argument); // Year < 0
}

TEST(DateTest, CopyConstructor) {
    Date d1(15, 6, 2024);
    Date d2(d1);
    EXPECT_EQ(d2.get_day(), 15);
    EXPECT_EQ(d2.get_month(), 6);
    EXPECT_EQ(d2.get_year(), 2024);
}

TEST(DateTest, MoveConstructor) {
    Date d1(15, 6, 2024);
    Date d2(std::move(d1));
    EXPECT_EQ(d2.get_day(), 15);
    EXPECT_EQ(d2.get_month(), 6);
    EXPECT_EQ(d2.get_year(), 2024);
}

// Assignment Operator Tests
TEST(DateTest, CopyAssignment) {
    Date d1(15, 6, 2024);
    Date d2;
    d2 = d1;
    EXPECT_EQ(d2.get_day(), 15);
    EXPECT_EQ(d2.get_month(), 6);
    EXPECT_EQ(d2.get_year(), 2024);
}

TEST(DateTest, MoveAssignment) {
    Date d1(15, 6, 2024);
    Date d2;
    d2 = std::move(d1);
    EXPECT_EQ(d2.get_day(), 15);
    EXPECT_EQ(d2.get_month(), 6);
    EXPECT_EQ(d2.get_year(), 2024);
}

TEST(DateTest, SelfAssignment) {
    Date d(1, 1, 2024);
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wself-assign-overloaded"
    d = d; // Self-assignment should not crash
#pragma clang diagnostic pop
    EXPECT_EQ(d.get_day(), 1);
    EXPECT_EQ(d.get_month(), 1);
    EXPECT_EQ(d.get_year(), 2024);
}

// Setter and Getter Tests
TEST(DateTest, SetDayValid) {
    Date d(1, 1, 2024);
    d.set_day(15);
    EXPECT_EQ(d.get_day(), 15);
    EXPECT_EQ(d.get_month(), 1);
    EXPECT_EQ(d.get_year(), 2024);
}

TEST(DateTest, SetDayInvalid) {
    Date d(1, 1, 2024);
    EXPECT_THROW(d.set_day(0), std::invalid_argument);
    EXPECT_THROW(d.set_day(32), std::invalid_argument);
    Date d2(1, 2, 2024);
    EXPECT_THROW(d2.set_day(30), std::invalid_argument); // February in leap year
}

TEST(DateTest, SetMonthValid) {
    Date d(1, 1, 2024);
    d.set_month(12);
    EXPECT_EQ(d.get_day(), 1);
    EXPECT_EQ(d.get_month(), 12);
    EXPECT_EQ(d.get_year(), 2024);
}

TEST(DateTest, SetMonthInvalid) {
    Date d(1, 1, 2024);
    EXPECT_THROW(d.set_month(0), std::invalid_argument);
    EXPECT_THROW(d.set_month(13), std::invalid_argument);
    Date d2(31, 1, 2024);
    EXPECT_THROW(d2.set_month(4), std::invalid_argument); // April has 30 days
}

TEST(DateTest, SetYearValid) {
    Date d(1, 1, 2024);
    d.set_year(2023);
    EXPECT_EQ(d.get_day(), 1);
    EXPECT_EQ(d.get_month(), 1);
    EXPECT_EQ(d.get_year(), 2023);
    Date d2(29, 2, 2024);
    EXPECT_THROW(d2.set_year(2023), std::invalid_argument); // February in non-leap year
}

TEST(DateTest, SetYearInvalid) {
    Date d(1, 1, 2024);
    EXPECT_THROW(d.set_year(-1), std::invalid_argument);
}

// GetDayName Tests
TEST(DateTest, GetDayName) {
    Date d; // Object for calling member function; actual date doesn't matter
    EXPECT_EQ(d.get_day_name(1, 1, 2024), "Monday");
    EXPECT_EQ(d.get_day_name(29, 2, 2024), "Thursday");
    EXPECT_EQ(d.get_day_name(25, 12, 2023), "Monday");
    EXPECT_EQ(d.get_day_name(4, 7, 1776), "Thursday");
}

// GetFormattedDate Tests
TEST(DateTest, GetFormattedDate) {
    Date d(1, 1, 2024);
    EXPECT_EQ(d.get_formatted_date(DateFormats::DAY_MONTH_YEAR), "1/1/2024");
    EXPECT_EQ(d.get_formatted_date(DateFormats::MONTH_DAY_YEAR), "1/1/2024");
    EXPECT_EQ(d.get_formatted_date(DateFormats::YEAR_MONTH_DAY), "2024/1/1");
    EXPECT_EQ(d.get_formatted_date(DateFormats::DAY_MONTH_YEAR_NAME), "1/1/2024 Monday");
    EXPECT_EQ(d.get_formatted_date(DateFormats::MONTH_DAY_YEAR_NAME), "1/1/2024 Monday");
    EXPECT_EQ(d.get_formatted_date(DateFormats::YEAR_MONTH_DAY_NAME), "2024/1/1 Monday");

    Date d2(2, 3, 2024); // To distinguish formats
    EXPECT_EQ(d2.get_formatted_date(DateFormats::DAY_MONTH_YEAR), "2/3/2024");
    EXPECT_EQ(d2.get_formatted_date(DateFormats::MONTH_DAY_YEAR), "3/2/2024");
    EXPECT_EQ(d2.get_formatted_date(DateFormats::YEAR_MONTH_DAY), "2024/3/2");
}

// Comparison Operator Tests
TEST(DateTest, ComparisonOperators) {
    Date d1(1, 1, 2024);
    Date d2(2, 1, 2024);
    Date d3(1, 2, 2024);
    Date d4(1, 1, 2025);
    Date d5(1, 1, 2024);

    EXPECT_TRUE(d1 == d5);
    EXPECT_FALSE(d1 == d2);
    EXPECT_TRUE(d1 != d2);
    EXPECT_FALSE(d1 != d5);
    EXPECT_TRUE(d1 < d2);
    EXPECT_TRUE(d2 > d1);
    EXPECT_TRUE(d1 <= d2);
    EXPECT_TRUE(d2 >= d1);
    EXPECT_TRUE(d1 <= d5);
    EXPECT_TRUE(d1 >= d5);
    EXPECT_TRUE(d1 < d3);
    EXPECT_TRUE(d3 < d4);
    EXPECT_TRUE(d4 > d1);
}

// Arithmetic Operator Tests
TEST(DateTest, ArithmeticOperators) {
    Date d(1, 1, 2024);
    Date d2 = d + 10;
    EXPECT_EQ(d2.get_day(), 11);
    EXPECT_EQ(d2.get_month(), 1);
    EXPECT_EQ(d2.get_year(), 2024);

    Date d3 = d + 31; // Crosses month
    EXPECT_EQ(d3.get_day(), 1);
    EXPECT_EQ(d3.get_month(), 2);
    EXPECT_EQ(d3.get_year(), 2024);

    Date d4 = d - 1; // Crosses year
    EXPECT_EQ(d4.get_day(), 31);
    EXPECT_EQ(d4.get_month(), 12);
    EXPECT_EQ(d4.get_year(), 2023);

    Date d5(28, 2, 2024);
    Date d6 = d5 + 1; // Leap year
    EXPECT_EQ(d6.get_day(), 29);
    EXPECT_EQ(d6.get_month(), 2);
    EXPECT_EQ(d6.get_year(), 2024);

    Date d7 = d6 + 1;
    EXPECT_EQ(d7.get_day(), 1);
    EXPECT_EQ(d7.get_month(), 3);
    EXPECT_EQ(d7.get_year(), 2024);

    Date d8 = d + (-1); // Negative addition
    EXPECT_EQ(d8.get_day(), 31);
    EXPECT_EQ(d8.get_month(), 12);
    EXPECT_EQ(d8.get_year(), 2023);

    // Test += and -=
    Date d9(1, 1, 2024);
    d9 += 15;
    EXPECT_EQ(d9.get_day(), 16);
    EXPECT_EQ(d9.get_month(), 1);
    EXPECT_EQ(d9.get_year(), 2024);

    d9 -= 15;
    EXPECT_EQ(d9.get_day(), 1);
    EXPECT_EQ(d9.get_month(), 1);
    EXPECT_EQ(d9.get_year(), 2024);

    Date d10(1, 3, 2024);
    d10 -= 1; // From March 1 to February 29
    EXPECT_EQ(d10.get_day(), 29);
    EXPECT_EQ(d10.get_month(), 2);
    EXPECT_EQ(d10.get_year(), 2024);
}

// Stream Operator Tests
TEST(DateTest, StreamOutput) {
    Date d(15, 6, 2024);
    std::ostringstream os;
    os << d;
    EXPECT_EQ(os.str(), "15/6/2024");
}

TEST(DateTest, StreamInputValid) {
    Date d;
    std::istringstream is("15/6/2024");
    is >> d;
    EXPECT_FALSE(is.fail());
    EXPECT_EQ(d.get_day(), 15);
    EXPECT_EQ(d.get_month(), 6);
    EXPECT_EQ(d.get_year(), 2024);
}

TEST(DateTest, StreamInputInvalidFormat) {
    Date d;
    std::istringstream is("15-6-2024"); // Wrong delimiters
    EXPECT_THROW(is >> d, std::invalid_argument);


    std::istringstream is2("15 6 2024"); // No delimiters
    EXPECT_THROW(is2 >> d, std::invalid_argument);
}

TEST(DateTest, StreamInputInvalidDate) {
    Date d;
    std::istringstream is("0/1/2024"); // Invalid day
    EXPECT_THROW(is >> d, std::invalid_argument);

    std::istringstream is2("31/4/2024"); // April has 30 days
    EXPECT_THROW(is2 >> d, std::invalid_argument);

    std::istringstream is3("29/2/2023"); // Non-leap year
    EXPECT_THROW(is3 >> d, std::invalid_argument);

    // Unchanged because of invalid date
    EXPECT_EQ(d.get_day(), 1);
    EXPECT_EQ(d.get_month(), 1);
    EXPECT_EQ(d.get_year(), 2024);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
