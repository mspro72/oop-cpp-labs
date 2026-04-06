#pragma once
#include <iostream>
using namespace std;

bool isValidDate(int year, int month, int day);
bool isValidTime(int hour, int minute, int second); // НОВОЕ

class DateTimeException {};

class DateTime {
private:
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;

    long long toJDN() const;
    void fromJDN(long long jdn);

public:
    DateTime(int year, int month, int day, int hour = 0, int minute = 0, int second = 0);
    DateTime();

    bool isLeapYear() const;
    int  daysInMonth() const;
    int dayOfWeek() const;

    DateTime& setYear(int year);
    DateTime& setMonth(int month);
    DateTime& setDay(int day);
    DateTime& setHour(int hour);
    DateTime& setMinute(int minute);
    DateTime& setSecond(int second);
    DateTime& setDate(int year, int month, int day);
    DateTime& setTime(int hour, int minute, int second);

    const DateTime& getDate(int& year, int& month, int& day) const;
    const DateTime& getYear(int& year) const;
    const DateTime& getMonth(int& month) const;
    const DateTime& getDay(int& day) const;
    const DateTime& getTime(int& hour, int& minute, int& second) const;
    const DateTime& getHour(int& hour) const;
    const DateTime& getMinute(int& minute) const;
    const DateTime& getSecond(int& second) const;

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