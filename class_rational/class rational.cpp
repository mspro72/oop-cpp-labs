#include <iostream>
#include "Rational.h"
#include <locale.h>

using namespace std;


Rational sqrt(Rational a) {
	//Вид sqrt(Rational(1, 2)) означает, что мы хотим найти квадратный корень из 1/2
	//Поличаетс вид вместо sqrt(a/b) получится sqrt(a*b)/b
	long long n_val = (long long)a.getNum() * a.getDen();

	//Если число отрицательное или нулевое, то квадратного корня не существует или он равен нулю
	if (n_val < 0) return Rational(0);
	if (n_val == 0) return Rational(0);

	//Первое приближение челая часть квадратного корня
	long long a0 = 0;
	while ((a0 + 1) * (a0 + 1) <= n_val) {
		a0++;
	}

	//Если число является полным квадратом, то возвращаем его квадратный корень
	if (a0 * a0 == n_val) {
		return Rational((int)a0, a.getDen());
	}

	//Длина цепной дроби и место где хранятся элементы приближений
	const int N = 6;
	Rational cf[N];

	// Параметры для вычисления цепной дроби
	long long m = 0;
	long long d = 1;
	long long curr_a = a0;

	// Вычисляем первые N элементов цепной дроби для sqrt(n_val)
	for (int i = 0; i < N; i++) {
		// Сохраняем текущее приближение
		cf[i] = Rational((int)curr_a);

		// Вычисляем следующие параметры для цепной дроби
		m = d * curr_a - m;
		d = (n_val - m * m) / d;
		curr_a = (a0 + m) / d;
	}
	// Вычисляем приближение к sqrt(n_val) используя элементы цепной дроби
	// Начинаем с последнего элемента и последовательно добавляем к нему обратные значения предыдущих элементов
	// Это позволяет получить более точное приближение к sqrt(n_val) по мере добавления элементов цепной дроби
	// Результат делим на знаменатель исходной дроби, чтобы получить приближение к sqrt(a)
	// Например, если a = 1/2, то n_val = 1*2 = 2. Цепная дробь для sqrt(2) начинается с 1, затем 2, затем 2, и так далее. При добавлении этих элементов мы получаем приближения к sqrt(2), которые затем делим на 2 (знаменатель исходной дроби), чтобы получить приближение к sqrt(1/2)
	Rational result = cf[N - 1];
	for (int i = N - 2; i >= 0; i--) {
		result = cf[i] + Rational(Rational(1), result);
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


	Rational a(1), b(-10), c(21);
	Rational Zero;

	if (a == Zero) {
		cout << "Это линейное уравнение!" << endl;
	}
	else {
		Rational D = b * b - Rational(4) * a * c;

		if (D > Zero) {
			Rational x1 = (-b + sqrt(D)) / (Rational(2) * a);
			Rational x2 = (-b - sqrt(D)) / (Rational(2) * a);
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

