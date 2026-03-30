#include <iostream>
#include <locale.h>
#include "datetime.h"

using namespace std;

DateTime EasterSunday(int year) {
    int a = year % 4;
    int b = year % 7;
    int c = year % 19;
    int d = (19 * c + 15) % 30;
    int e = (2 * a + 4 * b - d + 34) % 7;
    int month = (d + e + 114) / 31;
    int day = (d + e + 114) % 31 + 1;

    int century = year / 100;
    int diff = century - century / 4 - 2;

    DateTime julian(year, month, day);
    return julian + diff;
}

int main() {
	setlocale(LC_ALL, "rus");
    cout << "Конструкторы" << endl;
    DateTime d1;
    cout << "По умолчанию: " << d1 << endl;

    DateTime d2(2024, 2, 29);
    cout << "2024-02-29 (високосный): " << d2 << endl;

    try {
        DateTime d3(2023, 2, 29); // не високосный
        cout << "Ошибка: не должно было создаться" << endl;
    }
    catch (const DateTimeException&) {
        cout << "Исключение поймано: 2023-02-29 — невалидная дата" << endl;
    }

    cout << "\nisLeapYear / daysInMonth" << endl;
    DateTime d4(2024, 1, 1);
    cout << "2024 високосный? " << (d4.isLeapYear() ? "да" : "нет") << endl;
    cout << "Дней в феврале 2024: " << DateTime(2024, 2, 1).daysInMonth() << endl;

    DateTime d5(2023, 1, 1);
    cout << "2023 високосный? " << (d5.isLeapYear() ? "да" : "нет") << endl;
    cout << "Дней в феврале 2023: " << DateTime(2023, 2, 1).daysInMonth() << endl;

    cout << "\nАрифметика" << endl;
    DateTime d6(2024, 12, 30);
    cout << d6 << " + 3 дня = " << (d6 + 3) << endl;
    cout << d6 << " - 5 дней = " << (d6 - 5) << endl;

    DateTime d7(2025, 1, 1);
    cout << "Разница между " << d7 << " и " << d6 << ": "
        << (d7 - d6) << " дн." << endl;

    cout << "\nИнкремент / декремент" << endl;
    DateTime d8(2025, 3, 31);
    cout << "До ++: " << d8 << endl;
    ++d8;
    cout << "После ++: " << d8 << endl;
    d8++;
    cout << "После ++: " << d8 << endl;
    --d8;
    cout << "После --: " << d8 << endl;

    cout << "\nСравнение" << endl;
    DateTime a(2024, 6, 1), b(2024, 6, 15);
    cout << a << " < " << b << " : " << (a < b ? "да" : "нет") << endl;
    cout << a << " == " << b << " : " << (a == b ? "да" : "нет") << endl;
    cout << a << " != " << b << " : " << (a != b ? "да" : "нет") << endl;

    cout << "\nВвод из потока" << endl;
    DateTime d9;
    cout << "Введите дату (ГГГГ-ММ-ДД): ";
    if (cin >> d9)
        cout << "Прочитано: " << d9 << endl;
    else
        cout << "Невалидная дата" << endl;

    cout << "\nДата Пасхи в 2026 году" << endl;
	DateTime easter2026 = EasterSunday(2026);
	cout << "Пасха 2026: " << easter2026 << endl;
    cout << "\nДата Пасхи в 2126 году" << endl;
    DateTime easter2126 = EasterSunday(2126);
    cout << "Пасха 2126: " << easter2126 << endl;
    return 0;
}