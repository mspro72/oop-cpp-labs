#include <iostream>
#include "Rational.h"
#include <locale.h>
#include <vector>

using namespace std;


Rational sqrt(Rational a, int iterations = 6) {
	long long n_val = (long long)a.getNum() * a.getDen();

	if (n_val < 0) return Rational(0);
	if (n_val == 0) return Rational(0);

	long long a0 = 0;
	while ((a0 + 1) * (a0 + 1) <= n_val) {
		a0++;
	}

	if (a0 * a0 == n_val) {
		return Rational((int)a0, a.getDen());
	}

	vector<Rational> cf;
	cf.reserve(iterations);

	long long m = 0;
	long long d = 1;
	long long curr_a = a0;


	for (int i = 0; i < iterations; i++) {
		cf.push_back(Rational((int)curr_a));

		m = d * curr_a - m;
		d = (n_val - m * m) / d;
		curr_a = (a0 + m) / d;
	}

	Rational result = cf.back();
	for (int i = (int)cf.size() - 2; i >= 0; i--) {
		result = cf[i] + Rational(1) / result;
	}

	return result / Rational(a.getDen());
}

int main()
{
	setlocale(LC_ALL, "rus");
	/*setlocale(LC_ALL, "rus");
	Rational a(1, 2), b(-1, 6);
	cout << "a=" << a << " b=" << b << " a+b=" << a + b << endl;
	cout << "a(" << a << ") *= b(" << b << ")" << endl;
	a *= b;
	cout << "a=" << a << " b=" << b << " a-b=" << a - b << endl;
	Rational c = 3;
	cout << "b=" << b << " c=" << c << " b/c=" << b / c << endl;
	
	Rational e(7, 8), f(5, 12);
	cout << "e=" << e << " f=" << f << " e+f=?" << endl;
	cout << "Введите результат g=m/n в формате: m n" << endl;
	Rational g;
	cin >> g;
	if (g == Rational(0, 1)) {
		g = e + f;
	}
	if (e + f != g)
		cout << "Неправильно! e+f=" << e + f << endl;
	else
		cout << "Правильно!" << endl;*/

	Rational z(9);
	Rational x(5);
	Rational xl (121);
	cout << "Квадратный корень из " << (double)z << " равен " << (double)sqrt(z) << endl;
	cout << endl;
	cout << "Квадратный корень из " << (double)x << " равен " << (double)sqrt(x) << " или " << sqrt(x) << endl;
	cout << endl;
	cout << "Квадратный корень из " << (double)xl << " равен " << (double)sqrt(xl) << endl;
	cout << endl;


	Rational a(1), b(-1, 21), c(-2, 21);
	Rational Zero;

	if (a == Zero) {
		cout << "Это линейное уравнение!" << endl;
	}
	else {
		Rational D = b * b -(a * c)*4;

		if (D > Zero) {
			Rational x1 = (-b + sqrt(D)) / (a * 2);
			Rational x2 = (-b - sqrt(D)) / (a * 2);
			cout << "x1=" << x1 << " " << " x2=" << x2 << endl;
			cout << "x1=" << double(x1) << " " << " x2=" << double(x2) << endl;
		}
		else if (D == Zero) {
			Rational x1 = (-b) / (Rational(2) * a);
			cout << "x1=" << x1 << endl;
		}
		else {
			cout << "Корней нет" << endl;
		}
	}
}

