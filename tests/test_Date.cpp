#include "Date.hpp"
#include <gtest/gtest.h>

TEST(DateTest, DefaultConstructor) 
{
    Date date;
    EXPECT_EQ(date.get_day(), 1);
    EXPECT_EQ(date.get_month(), 1);
    EXPECT_EQ(date.get_year(), 2024);
}

TEST(DateTest, ParameterizedConstructorValid) 
{
    Date date(25, 12, 2023);
    EXPECT_EQ(date.get_day(), 25);
    EXPECT_EQ(date.get_month(), 12);
    EXPECT_EQ(date.get_year(), 2023);
}

TEST(DateTest, ParameterizedConstructorInvalid) 
{
    EXPECT_THROW(Date date(32, 1, 2024), std::invalid_argument);
}

TEST(DateTest, CopyConstructor) 
{
    Date date1(15, 6, 2020);
    Date date2 = date1;
    EXPECT_EQ(date2.get_day(), 15);
    EXPECT_EQ(date2.get_month(), 6);
    EXPECT_EQ(date2.get_year(), 2020);
}

TEST(DateTest, MoveConstructor) 
{
    Date date1(15, 6, 2020);
    Date date2 = std::move(date1);
    EXPECT_EQ(date2.get_day(), 15);
    EXPECT_EQ(date2.get_month(), 6);
    EXPECT_EQ(date2.get_year(), 2020);
}

TEST(DateTest, CopyAssignmentOperator) 
{
    Date date1(15, 6, 2020);
    Date date2;
    date2 = date1;
    EXPECT_EQ(date2.get_day(), 15);
    EXPECT_EQ(date2.get_month(), 6);
    EXPECT_EQ(date2.get_year(), 2020);
}

TEST(DateTest, MoveAssignmentOperator) 
{
    Date date1(15, 6, 2020);
    Date date2;
    date2 = std::move(date1);
    EXPECT_EQ(date2.get_day(), 15);
    EXPECT_EQ(date2.get_month(), 6);
    EXPECT_EQ(date2.get_year(), 2020);
}

TEST(DateTest, Setters) 
{
    Date date;
    date.set_day(15);
    date.set_month(6);
    date.set_year(2020);
    EXPECT_EQ(date.get_day(), 15);
    EXPECT_EQ(date.get_month(), 6);
    EXPECT_EQ(date.get_year(), 2020);
}

TEST(DateTest, InvalidSetters) 
{
    Date date;
    EXPECT_THROW(date.set_day(32), std::invalid_argument);
    EXPECT_THROW(date.set_month(13), std::invalid_argument);
    EXPECT_THROW(date.set_year(-1), std::invalid_argument);
}

TEST(DateTest, GetFormattedDate) 
{
    Date date(15, 6, 2020);
    EXPECT_EQ(date.get_formatted_date(1), "15/6/2020");
    EXPECT_EQ(date.get_formatted_date(2), "15/June/2020");
    EXPECT_EQ(date.get_formatted_date(3), "Monday 15.6.2020");
}

TEST(DateTest, ComparisonOperators) 
{
    Date date1(15, 6, 2020);
    Date date2(16, 6, 2020);
    EXPECT_TRUE(date1 < date2);
    EXPECT_TRUE(date2 > date1);
    EXPECT_TRUE(date1 <= date2);
    EXPECT_TRUE(date2 >= date1);
    EXPECT_FALSE(date1 == date2);
    EXPECT_TRUE(date1 != date2);
}

TEST(DateTest, StreamOperators) 
{
    Date date(15, 6, 2020);
    std::ostringstream os;
    os << date;
    EXPECT_EQ(os.str(), "15/6/2020");

    std::istringstream is("16/6/2020");
    is >> date;
    EXPECT_EQ(date.get_day(), 16);
    EXPECT_EQ(date.get_month(), 6);
    EXPECT_EQ(date.get_year(), 2020);
}

int main(int argc, char **argv) 
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
