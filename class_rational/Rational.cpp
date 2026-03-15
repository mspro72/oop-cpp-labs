#include "Rational.h"

Rational::Rational() {
    num = 0;
    den = 1;
}

Rational::Rational(int n) {
    num = n;
    den = 1;
}

Rational::Rational(int n, int d) {
    num = n;
    den = d;
    simplify();
}

void Rational::simplify() {
    int a = num;
    int b = den;
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    num /= a;
    den /= a;
}

Rational& Rational::operator+=(const Rational& r) {
    num = num * r.den + den * r.num;
    den = den * r.den;
    simplify();
    return *this;
}

Rational Rational::operator+(const Rational& r) const {
    Rational R(*this);
    return R += r;
}

Rational Rational::operator-() const {
    Rational r(-num, den);
    return r;
}

Rational& Rational::operator-=(const Rational& r) {
    return (*this += (-r));
}

Rational Rational::operator-(const Rational& r) const {
    Rational R(*this);
    return R -= r;
}

Rational& Rational::operator*=(const Rational& r) {
    num = num * r.num;
    den = den * r.den;
    simplify();
    return *this;
}

Rational Rational::operator*(const Rational& r) const {
    Rational R(*this);
    return R *= r;
}

Rational& Rational::operator/=(const Rational& r) {
    num *= r.den;
    den *= r.num;
    simplify();
    return *this;
}

Rational Rational::operator/(const Rational& r) const {
    Rational res(*this);
    return res /= r;
}

Rational& Rational::operator++() {
    num += den;
    return *this;
}

Rational Rational::operator++(int) {
    Rational r(*this);
    num += den;
    return r;
}

bool Rational::operator==(const Rational& r) const {
    return (num == r.num) && (den == r.den);
}

bool Rational::operator!=(const Rational& r) const {
    return !(*this == r);
}

bool Rational::operator<(const Rational& r) const {
    return num * r.den < r.num * den;
}

bool Rational::operator>(const Rational& r) const {
    return r < *this;
}

bool Rational::operator<=(const Rational& r) const {
    return !(r < *this);
}

bool Rational::operator>=(const Rational& r) const {
    return !(*this < r);
}

Rational::operator int() const {
    return num / den;
}

Rational::operator double() const {
    return ((double)num) / den;
}

istream& operator >>(istream& in, Rational& r)
{
    in >> r.num >> r.den;
    return in;
}
ostream& operator <<(ostream& out, const Rational& r)
{
    out << r.num << "/" << r.den;
    return out;
}