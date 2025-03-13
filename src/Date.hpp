#pragma once
#include <unordered_map>
#include <string>
#include <utility>


enum class DateFormats
{
    DAY_MONTH_YEAR,
    MONTH_DAY_YEAR,
    YEAR_MONTH_DAY,
    DAY_MONTH_YEAR_NAME,
    MONTH_DAY_YEAR_NAME,
    YEAR_MONTH_DAY_NAME
};


class Date
{
    int day;
    int month;
    int year;

    static const int length_of_each_month[12];
    static const std::string day_names[7];
    static const std::string month_names[12];

public:
    // Constructors
    Date(int day = 1, int month = 1, int year = 2024);
    Date(const std::string& date);
    Date(const Date& other);    
    Date(Date&& other) noexcept;                 
    Date& operator=(const Date&);                      
    Date& operator=(Date&& other) noexcept;                  
    

    // Setters
    int get_day() const;
    int get_month() const;
    int get_year() const;

    // Getters
    void set_day(const int new_day);
    void set_month(const int new_month);
    void set_year(const int new_year);

    // Check date
    bool check_date(const int day, const int month, const int year) const;
    bool is_leap_year(const int year) const;

    // Format getters
    std::string get_day_name(int day, int month, int year) const;
    std::string get_formatted_date(const DateFormats format) const;

    // Logic operators
    bool operator==(const Date& other) const;
    bool operator!=(const Date& other) const;
    bool operator>(const Date& other) const;
    bool operator<(const Date& other) const;
    bool operator<=(const Date& other) const;
    bool operator>=(const Date& other) const;

    // Arithmetic operators
    Date operator+(const int days) const;
    Date operator-(const int days) const;
    Date& operator+=(const int days);
    Date& operator-=(const int days);

    // Streams
    friend std::ostream& operator<<(std::ostream& os, const Date& date);
    friend std::istream& operator>>(std::istream& is, Date& date);
};
