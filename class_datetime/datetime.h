#pragma once
#include <iostream>
using namespace std;

bool isValidDate(int year, int month, int day);

class DateTimeException {};

class DateTime {
private:
    int year;
    int month;
    int day;

    long long toJDN() const;
    void fromJDN(long long jdn);

public:
    DateTime(int year, int month, int day);
    DateTime();

    bool isLeapYear() const;
    int  daysInMonth() const;

    DateTime& setYear(int year);
    DateTime& setMonth(int month);
    DateTime& setDay(int day);
    DateTime& setDate(int year, int month, int day);

    const DateTime& getDate(int& year, int& month, int& day) const;
    const DateTime& getYear(int& year) const;
    const DateTime& getMonth(int& month) const;
    const DateTime& getDay(int& day) const;

    DateTime  operator+(int days) const;
    DateTime  operator-(int days) const;
    long long operator-(const DateTime& other) const;

    DateTime  operator++(int);
    DateTime  operator--(int);
    DateTime& operator++();
    DateTime& operator--();

    DateTime& operator=(const DateTime& other);

    bool operator>(const DateTime& other) const;
    bool operator<(const DateTime& other) const;
    bool operator==(const DateTime& other) const;
    bool operator!=(const DateTime& other) const;
    bool operator>=(const DateTime& other) const;
    bool operator<=(const DateTime& other) const;

    friend ostream& operator<<(ostream& out, const DateTime& dt);
    friend istream& operator>>(istream& in, DateTime& dt);
};