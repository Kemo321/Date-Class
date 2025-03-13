#include "Date.hpp"
#include <iostream>

Date::Date(int day, int month, int year) : day(day), month(month), year(year) 
{
    if (!this->check_date(day, month, year))
        throw std::invalid_argument("Incorrect date");
};

Date::Date(const Date& other) : day(other.day), month(other.month), year(other.year) {}
Date::Date(Date&& other) noexcept : day(other.day), month(other.month), year(other.year) {}

Date& Date::operator=(const Date& other) 
{
    if (this == &other) 
    {
        return *this;
    }
    this->day = other.day;
    this->month = other.month;
    this->year = other.year;
    return *this;
}

Date& Date::operator=(Date&& other) noexcept 
{
    if (this == &other) 
    {
        return *this;
    }
    this->day = other.day;
    this->month = other.month;
    this->year = other.year;
    return *this;
}

int Date::get_day() const
{
    return this->day;
};

void Date::set_day(const int new_day)
{
    if (this->check_date(new_day, this->month, this->year))
    {
        this->day = new_day;
    }
    else 
        throw std::invalid_argument("Incorrect date");
};

int Date::get_month() const
{
    return this->month;
};

void Date::set_month(const int new_month)
{
    if (this->check_date(this->day, new_month, this->year))
    {
        this->month = new_month;
    }
    else 
        throw std::invalid_argument("Incorrect date");
}

int Date::get_year() const
{
    return this->year;
};

void Date::set_year(const int new_year)
{
    if (check_date(this->day, this->month, new_year))
    {
        this->year = new_year;
    }
    else 
        throw std::invalid_argument("Incorrect date");
};

std::string Date::get_day_name(int day, int month, int year) const
{
    // Zeller's Congruence algorithm
    if (month < 3)
    {
        month += 12;
        year--;
    }

    int k = year % 100;
    int j = year / 100;

    int day_index = (day + ((13 * (month + 1)) / 5) + k + (k / 4) + (j / 4) - (2 * j)) % 7;
    day_index = (day_index + 7) % 7;
    return this->day_names[day_index];
};

std::string Date::get_formatted_date(const DateFormats format) const
{
    
    switch(format)
    {
        case DateFormats::DAY_MONTH_YEAR:
            return (std::to_string(this->day) + "/" + std::to_string(this->month) + "/" + std::to_string(this->year));
            break;

        case DateFormats::MONTH_DAY_YEAR:
            return (std::to_string(this->month) + "/" + std::to_string(this->day) + "/" + std::to_string(this->year));
            break;
        case DateFormats::YEAR_MONTH_DAY:
            return (std::to_string(this->year) + "/" + std::to_string(this->month) + "/" + std::to_string(this->day));
            break;
        case DateFormats::DAY_MONTH_YEAR_NAME:
            return (std::to_string(this->day) + "/" + std::to_string(this->month) + "/" + std::to_string(this->year) + " " + this->get_day_name(this->day, this->month, this->year));
            break;
        case DateFormats::MONTH_DAY_YEAR_NAME:
            return (std::to_string(this->month) + "/" + std::to_string(this->day) + "/" + std::to_string(this->year) + " " + this->get_day_name(this->day, this->month, this->year));
            break;
        case DateFormats::YEAR_MONTH_DAY_NAME:
            return (std::to_string(this->year) + "/" + std::to_string(this->month) + "/" + std::to_string(this->day) + " " + this->get_day_name(this->day, this->month, this->year));
            break;
        default:
            return (std::to_string(this->day) + "/" + std::to_string(this->month) + "/" + std::to_string(this->year));
            break;
    }
};

bool Date::check_date(int day, int month, int year) const
{
    return
    (
        year >= 0 &&
        month > 0 &&
        month < 13 &&
        day > 0 &&
        (
        (day <= this->length_of_each_month[month - 1])
        ||
        (day == 29 && month == 2 && this->is_leap_year(year))
        )
    );
}

bool Date::is_leap_year(int year) const
{
    return ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0);
}

bool Date::operator==(const Date& other) const 
{
    return (this->day == other.get_day() && this->month == other.get_month() && this->year == other.get_year());
}

bool Date::operator!=(const Date& other) const
{
    return !this->operator==(other);
}

bool Date::operator>(const Date& other) const 
{
    return !(*this <= other);
}

bool Date::operator<(const Date& other) const 
{
    if (this->year < other.get_year())
    {
        return true;
    }
    else if (this->year > other.get_year())
    {
        return false;
    }

    if (this->month < other.get_month())
    {
        return true;
    }
    else if (this->month > other.get_month())
    {
        return false;
    }

    return this->day < other.get_day();
}

bool Date::operator<=(const Date& other) const
{
    return (this->operator==(other) || this->operator<(other));
}

bool Date::operator>=(const Date& other) const
{
    return !(*this < other);
}

std::ostream& operator<<(std::ostream& os, const Date& date) 
{
    os << date.get_formatted_date(DateFormats::DAY_MONTH_YEAR);
    return os;
}

std::istream& operator>>(std::istream& is, Date& date) 
{
    char delimiter1, delimiter2;
    int day, month, year;
    is >> day >> delimiter1 >> month >> delimiter2 >> year;


    if (delimiter1 == '/' && delimiter2 == '/' && day > 0 && month > 0 && year >= 0 && date.check_date(day, month, year))
    {
        date.set_day(day);
        date.set_month(month);
        date.set_year(year);
    } else 
    {
        throw std::invalid_argument("Incorrect date");
    }

    return is;
}

Date Date::operator+(const int days) const
{
    Date new_date = *this;
    new_date += days;
    return new_date;
}

Date Date::operator-(const int days) const
{
    Date new_date = *this;
    new_date -= days;
    return new_date;
}

Date& Date::operator+=(const int days)
{
    if (days < 0)
    {
        return *this -= -days;
    }

    int days_to_add = days;
    while (days_to_add > 0)
    {
        int days_in_current_month = this->length_of_each_month[this->month - 1] - this->day + 1;

        if (this->is_leap_year(this->year) && this->month == 2)
        {
            days_in_current_month++;
        }

        if (days_in_current_month <= days_to_add)
        {
            days_to_add -= days_in_current_month;
            this->day = 1;
            if (this->month == 12)
            {
                this->month = 1;
                this->year++;
            }
            else
            {
                this->month++;
            }
        }
        else
        {
            this->day += days_to_add;
            days_to_add = 0;
        }
    }

    return *this;
}

Date& Date::operator-=(const int days)
{

    if (days < 0)
    {
        return *this += -days;
    }

    int days_to_subtract = days;
    while (days_to_subtract > 0)
    {
        if (this->day <= days_to_subtract)
        {
            days_to_subtract -= this->day;
            if (this->month == 1)
            {
                this->month = 12;
                this->year--;
            }
            else
            {
                this->month--;
            }
            this->day = this->length_of_each_month[this->month - 1];
            if (this->is_leap_year(this->year) && this->month == 2)
            {
                this->day++;
            }
        }
        else
        {
            this->day -= days_to_subtract;
            days_to_subtract = 0;
        }
    }

    return *this;
}

const int Date::length_of_each_month[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
const std::string Date::day_names[7] = {"Saturday", "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday"};
const std::string Date::month_names[12] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

