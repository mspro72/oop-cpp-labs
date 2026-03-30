#include "datetime.h"

long long DateTime::toJDN() const {
    long long a = (14 - month) / 12;
    long long Y = year + 4800 - a;
    long long M = month + 12 * a - 3;
    return day + (153 * M + 2) / 5
        + 365 * Y
        + Y / 4
        - Y / 100
        + Y / 400
        - 32045;
}

void DateTime::fromJDN(long long jdn) {
    long long f = jdn + 1401 + (((4 * jdn + 274277) / 146097) * 3) / 4 - 38;
    long long e = 4 * f + 3;
    long long g = (e % 1461) / 4;
    long long h = 5 * g + 2;

    day = (int)((h % 153) / 5 + 1);
    month = (int)((h / 153 + 2) % 12 + 1);
    year = (int)(e / 1461 - 4716 + (14 - month) / 12);
}

bool DateTime::isLeapYear() const {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int DateTime::daysInMonth() const {
    const int days[] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
    if (month == 2 && isLeapYear()) return 29;
    return days[month];
}

bool isValidDate(int year, int month, int day) {
    if (year < 1)                return false;
    if (month < 1 || month > 12) return false;
    const int days[] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
    bool leap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    int maxDay = (month == 2 && leap) ? 29 : days[month];
    if (day < 1 || day > maxDay) return false;
    return true;
}

DateTime::DateTime(int year, int month, int day) {
    if (!isValidDate(year, month, day))
        throw DateTimeException{};
    this->year = year;
    this->month = month;
    this->day = day;
}

DateTime::DateTime() : year(2000), month(1), day(1) {}

DateTime& DateTime::setYear(int year) {
    if (!isValidDate(year, this->month, this->day))
        throw DateTimeException{};
    this->year = year;
    return *this;
}

DateTime& DateTime::setMonth(int month) {
    if (!isValidDate(this->year, month, this->day))
        throw DateTimeException{};
    this->month = month;
    return *this;
}

DateTime& DateTime::setDay(int day) {
    if (!isValidDate(this->year, this->month, day))
        throw DateTimeException{};
    this->day = day;
    return *this;
}

DateTime& DateTime::setDate(int year, int month, int day) {
    if (!isValidDate(year, month, day))
        throw DateTimeException{};
    this->year = year;
    this->month = month;
    this->day = day;
    return *this;
}

const DateTime& DateTime::getDate(int& year, int& month, int& day) const {
    year = this->year;
    month = this->month;
    day = this->day;
    return *this;
}

const DateTime& DateTime::getYear(int& year) const {
    year = this->year;
    return *this;
}

const DateTime& DateTime::getMonth(int& month) const {
    month = this->month;
    return *this;
}

const DateTime& DateTime::getDay(int& day) const {
    day = this->day;
    return *this;
}

DateTime DateTime::operator+(int days) const {
    DateTime result;
    result.fromJDN(toJDN() + days);
    return result;
}

DateTime DateTime::operator-(int days) const {
    DateTime result;
    result.fromJDN(toJDN() - days);
    return result;
}

long long DateTime::operator-(const DateTime& other) const {
    return toJDN() - other.toJDN();
}

DateTime& DateTime::operator++() {
    fromJDN(toJDN() + 1);
    return *this;
}

DateTime DateTime::operator++(int) {
    DateTime tmp = *this;
    fromJDN(toJDN() + 1);
    return tmp;
}

DateTime& DateTime::operator--() {
    fromJDN(toJDN() - 1);
    return *this;
}

DateTime DateTime::operator--(int) {
    DateTime tmp = *this;
    fromJDN(toJDN() - 1);
    return tmp;
}

DateTime& DateTime::operator=(const DateTime& other) {
    if (this != &other) {
        year = other.year;
        month = other.month;
        day = other.day;
    }
    return *this;
}

bool DateTime::operator==(const DateTime& o) const { return toJDN() == o.toJDN(); }
bool DateTime::operator!=(const DateTime& o) const { return !(*this == o); }
bool DateTime::operator<(const DateTime& o)  const { return toJDN() < o.toJDN(); }
bool DateTime::operator>(const DateTime& o)  const { return o < *this; }
bool DateTime::operator<=(const DateTime& o) const { return !(o < *this); }
bool DateTime::operator>=(const DateTime& o) const { return !(*this < o); }

ostream& operator<<(ostream& out, const DateTime& dt) {
    out << dt.year
        << '-' << (dt.month < 10 ? "0" : "") << dt.month
        << '-' << (dt.day < 10 ? "0" : "") << dt.day;
    return out;
}

istream& operator>>(istream& in, DateTime& dt) {
    int y, m, d;
    char sep1, sep2;
    in >> y >> sep1 >> m >> sep2 >> d;
    if (!in) return in;
    if (!isValidDate(y, m, d)) {
        in.setstate(ios::failbit);
        return in;
    }
    dt.setDate(y, m, d);
    return in;
}