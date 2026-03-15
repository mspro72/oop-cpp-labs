#include <iostream>
#include "Rational.h"
#include <locale.h>
using namespace std;


Rational sqrt(Rational a) {
	Rational x = a;
	Rational half(1, 2);
	int MAX = 150000000;
	for (int i = 0; i < 15; i++) {
		Rational next_x = half * (x + (a / x));
		if (abs(next_x.getNum()) > MAX || abs(next_x.getDen()) > MAX) {
			break;
		}
		x = next_x;
	}
	return x;
}

int main()
{
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
	cout << sqrt(z) << "\t" << double(sqrt(z)) << endl;
	cout << endl;
	cout << sqrt(x) << "\t" << double(sqrt(x)) <<endl;
	cout << endl;
	cout << sqrt(xl) << "\t" << double(sqrt(xl)) << endl;
	cout << endl;


	Rational a(422), b(12), c(-67);
	Rational Zero;

	if (a == Zero) {
		cout << "Это линейное уравнение!" << endl;
	}
	else {
		Rational D = b * b - Rational(4) * a * c;

		if (D > Zero) {
			Rational x1 = (-b + sqrt(D)) / (Rational(2) * a);
			Rational x2 = (-b - sqrt(D)) / (Rational(2) * a);
			cout << "x1=" << x1 << "\t" << " x2=" << x2 << endl;
			cout << "x1=" << double(x1) << "\t" << " x2=" << double(x2) << endl;
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

