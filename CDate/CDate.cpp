#include <iostream>
#include "CDate.h"

CDate::CDate() : _day(1), _month(1), _year(1970) {}

int CDate::day() const noexcept {
    return _day;
}

int CDate::month() const noexcept {
    return _month;
}

int CDate::year() const noexcept {
    return _year;
}

bool CDate::isLeapYear(int year) const {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int CDate::daysInMonth(int month, int year) const {
    switch (month) {
    case 1: case 3: case 5: case 7: case 8: case 10: case 12:
        return 31;
    case 4: case 6: case 9: case 11:
        return 30;
    case 2:
        return isLeapYear(year) ? 29 : 28;
    default:
        return 0;
    }
}

CDate::CDate(int day, int month, int year) {
    if (year < 1) throw std::out_of_range("");
    if (month < 1 || month > 12) throw std::out_of_range("");

    int maxDays = daysInMonth(month, year);
    if (day < 1 || day > maxDays) throw std::out_of_range("");

    _day = day;
    _month = month;
    _year = year;
}

CDate::CDate(const CDate& other) : _day(other._day), _month(other._month), _year(other._year) {}

CDate::CDate(int day, int month) {
    if (month < 1 || month > 12) throw std::out_of_range("");

    int maxDays = daysInMonth(month, 1970);
    if (day < 1 || day > maxDays) throw std::out_of_range("");

    _day = day;
    _month = month;
    _year = 1970;
}

void CDate::day(int day) {
    int maxDays = daysInMonth(_month, _year);
    if (day < 1 || day > maxDays) throw std::out_of_range("");
    _day = day;
}

void CDate::month(int month) {
    if (month < 1 || month > 12) throw std::out_of_range("");

    int maxDays = daysInMonth(month, _year);
    if (_day > maxDays) {
        _day = maxDays;
    }
    _month = month;
}

void CDate::year(int year) {
    if (year < 1) throw std::out_of_range("");

    int maxDays = daysInMonth(_month, year);
    if (_day > maxDays) {
        _day = maxDays;
    }
    _year = year;
}

CDate CDate::add_days(int days) {
    CDate result(*this);

    while (days > 0) {
        int currentMonthDays = daysInMonth(result._month, result._year);
        if (result._day + days <= currentMonthDays) {
            result._day += days;
            days = 0;
        }
        else {
            days -= (currentMonthDays - result._day + 1);
            result._day = 1;
            result._month++;
            if (result._month > 12) {
                result._month = 1;
                result._year++;
            }
        }
    }
    return result;
}

CDate CDate::add_months(int months) {
    CDate result(*this);

    result._month += months;
    while (result._month > 12) {
        result._month -= 12;
        result._year++;
    }

    int maxDays = daysInMonth(result._month, result._year);
    if (result._day > maxDays) {
        result._day = maxDays;
    }

    return result;
}

CDate CDate::add_years(int years) {
    CDate result(*this);

    result._year += years;

    if (result._month == 2 && result._day == 29 && !isLeapYear(result._year)) {
        result._day = 28;
    }

    return result;
}