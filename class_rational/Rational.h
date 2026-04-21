#pragma once
#include <iostream>
using namespace std;

class Rational {
private:
    int num; 
    int den; 

    void simplify(); 

public:
    Rational();
    Rational(int n);
    Rational(int n, int d);
    Rational(Rational n, Rational d);

    Rational& operator+=(const Rational& r);
    Rational& operator-=(const Rational& r);
    Rational& operator*=(const Rational& r);
    Rational& operator/=(const Rational& r);

	Rational& operator+=(const int& n) const;
	Rational& operator-=(const int& n) const;
	Rational& operator*=(const int& n) const;
	Rational& operator/=(const int& n) const;

    Rational operator+(const Rational& r) const;
    Rational operator-(const Rational& r) const;
    Rational operator*(const Rational& r) const;
    Rational operator/(const Rational& r) const;

	Rational operator+(const int& n) const;
	Rational operator-(const int& n) const;
	Rational operator*(const int& n) const;
    Rational operator/(const int& n) const;

    Rational operator-() const;

    Rational& operator++();    // Префиксный
    Rational operator++(int);  // Постфиксный

    bool operator==(const Rational& r) const;
    bool operator!=(const Rational& r) const;

    bool operator<(const Rational& r) const;
    bool operator>(const Rational& r) const;
    bool operator<=(const Rational& r) const;
    bool operator>=(const Rational& r) const;

    operator int() const;
    operator double() const;

    int getNum() const { return num; };
    int getDen() const { return den; };

    friend istream& operator >>(istream& in, Rational& r);
    friend ostream& operator <<(ostream& out, const Rational& r);
};