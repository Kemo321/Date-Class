#include <unordered_map>
#include <string>
#include <utility>

class Date
{
    int day;
    int month;
    int year;
    const std::pair<int, std::string> length_of_each_month[12]
    {
        {31, "January"},
        {28, "February"},
        {31, "March"},
        {30, "April"},
        {31, "May"},
        {30, "June"},
        {31, "July"},
        {31, "August"},
        {30, "September"},
        {31, "October"},
        {30, "November"},
        {31, "December"}
    };

    const std::string day_name[7]
    {
        "Saturday",
        "Sunday",
        "Monday",
        "Tuesday",
        "Wednesday",
        "Thursday",
        "Friday"
    };

public:
    // Constructors
    Date(int c_day = 1, int c_month = 1, int c_year = 2024);
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

    // Format getters
    std::string get_day_name(int day, int month, int year) const;
    std::string get_formatted_date(const int format) const;

    // Logic operators
    bool operator==(const Date& other) const;
    bool operator!=(const Date& other) const;
    bool operator>(const Date& other) const;
    bool operator<(const Date& other) const;
    bool operator<=(const Date& other) const;
    bool operator>=(const Date& other) const;

    // Streams
    friend std::ostream& operator<<(std::ostream& os, const Date& date);
    friend std::istream& operator>>(std::istream& is, Date& date);
};

