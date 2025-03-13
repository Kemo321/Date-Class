
---

# Date Class Documentation

The `Date` class provides a way to handle and manipulate dates. It supports various operations such as setting and getting date components, formatting dates, comparing dates, and performing arithmetic operations on dates.

## Table of Contents
- [Enums and Constants](#enums-and-constants)
- [Constructors](#constructors)
- [Assignment Operators](#assignment-operators)
- [Getters and Setters](#getters-and-setters)
- [Utility Functions](#utility-functions)
- [Comparison Operators](#comparison-operators)
- [Arithmetic Operators](#arithmetic-operators)
- [Stream Operators](#stream-operators)
- [Examples](#examples)

---

## Enums and Constants

### DateFormats
An enumeration defining different formats for displaying the date:
- `DAY_MONTH_YEAR`: Day/Month/Year (e.g., 1/1/2024)
- `MONTH_DAY_YEAR`: Month/Day/Year (e.g., 1/1/2024)
- `YEAR_MONTH_DAY`: Year/Month/Day (e.g., 2024/1/1)
- `DAY_MONTH_YEAR_NAME`: Day/Month/Year DayName (e.g., 1/1/2024 Monday)
- `MONTH_DAY_YEAR_NAME`: Month/Day/Year DayName (e.g., 1/1/2024 Monday)
- `YEAR_MONTH_DAY_NAME`: Year/Month/Day DayName (e.g., 2024/1/1 Monday)

### Constants
- `length_of_each_month`: An array of integers representing the number of days in each month (non-leap year).
- `day_names`: An array of strings for the names of the days of the week.
- `month_names`: An array of strings for the names of the months.

---

## Constructors

### `Date(int day = 1, int month = 1, int year = 2024)`
Constructs a `Date` object with the given day, month, and year. Throws `std::invalid_argument` if the date is invalid.

### `Date(const std::string& date)`
Constructs a `Date` object from a string representation of the date. (Note: Specific format depends on implementation.)

### `Date(const Date& other)`
Copy constructor. Creates a new `Date` object as a copy of another `Date` object.

### `Date(Date&& other) noexcept`
Move constructor. Creates a new `Date` object by moving resources from another `Date` object.

---

## Assignment Operators

### `Date& operator=(const Date& other)`
Copy assignment operator. Assigns the values from another `Date` object.

### `Date& operator=(Date&& other) noexcept`
Move assignment operator. Moves the values from another `Date` object.

---

## Getters and Setters

### `int get_day() const`
Returns the day component of the date.

### `int get_month() const`
Returns the month component of the date.

### `int get_year() const`
Returns the year component of the date.

### `void set_day(const int new_day)`
Sets the day component of the date. Throws `std::invalid_argument` if the new day is invalid for the current month and year.

### `void set_month(const int new_month)`
Sets the month component of the date. Throws `std::invalid_argument` if the new month is invalid or if the current day is invalid for the new month.

### `void set_year(const int new_year)`
Sets the year component of the date. Throws `std::invalid_argument` if the new year is negative.

---

## Utility Functions

### `bool check_date(const int day, const int month, const int year) const`
Checks if the given day, month, and year form a valid date, considering leap years.

### `std::string get_day_name(int day, int month, int year) const`
Returns the name of the day for the given date.

### `std::string get_formatted_date(const DateFormats format) const`
Returns the date in the specified format as a string.

---

## Comparison Operators

The `Date` class overloads the following comparison operators:
- `bool operator==(const Date& other) const`
- `bool operator!=(const Date& other) const`
- `bool operator>(const Date& other) const`
- `bool operator<(const Date& other) const`
- `bool operator<=(const Date& other) const`
- `bool operator>=(const Date& other) const`

These operators allow comparing two `Date` objects based on their chronological order.

---

## Arithmetic Operators

### `Date operator+(const int days) const`
Returns a new `Date` object that is the result of adding the specified number of days to the current date.

### `Date operator-(const int days) const`
Returns a new `Date` object that is the result of subtracting the specified number of days from the current date.

### `Date& operator+=(const int days)`
Adds the specified number of days to the current date and returns a reference to the modified object.

### `Date& operator-=(const int days)`
Subtracts the specified number of days from the current date and returns a reference to the modified object.

---

## Stream Operators

### `friend std::ostream& operator<<(std::ostream& os, const Date& date)`
Outputs the date to the stream in the "day/month/year" format.

### `friend std::istream& operator>>(std::istream& is, Date& date)`
Inputs the date from the stream, expecting the format "day/month/year". Sets the failbit if the input is invalid.

---

## Examples

### Creating a Date Object
```cpp
Date d1(15, 6, 2024);  // Creates a date: June 15, 2024
Date d2("15/6/2024");  // Creates a date from string (assuming implementation)
```

### Getting and Setting Date Components
```cpp
Date d(1, 1, 2024);
std::cout << d.get_day() << "/" << d.get_month() << "/" << d.get_year() << std::endl;  // Outputs: 1/1/2024
d.set_day(15);
d.set_month(6);
d.set_year(2023);
std::cout << d.get_day() << "/" << d.get_month() << "/" << d.get_year() << std::endl;  // Outputs: 15/6/2023
```

### Formatting Dates
```cpp
Date d(1, 1, 2024);
std::cout << d.get_formatted_date(DateFormats::DAY_MONTH_YEAR) << std::endl;       // 1/1/2024
std::cout << d.get_formatted_date(DateFormats::MONTH_DAY_YEAR) << std::endl;       // 1/1/2024
std::cout << d.get_formatted_date(DateFormats::YEAR_MONTH_DAY) << std::endl;       // 2024/1/1
std::cout << d.get_formatted_date(DateFormats::DAY_MONTH_YEAR_NAME) << std::endl;  // 1/1/2024 Monday
```

### Comparing Dates
```cpp
Date d1(1, 1, 2024);
Date d2(2, 1, 2024);
if (d1 < d2) {
    std::cout << "d1 is before d2" << std::endl;
}
```

### Arithmetic Operations
```cpp
Date d(1, 1, 2024);
Date d2 = d + 10;  // January 11, 2024
Date d3 = d - 1;   // December 31, 2023
d += 15;           // January 16, 2024
```

### Stream Operations
```cpp
Date d;
std::cin >> d;  // Input: 15/6/2024
std::cout << d; // Output: 15/6/2024
```

---
