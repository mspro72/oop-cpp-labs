#include <iostream>
#include "field.h"
#include <locale.h>
using namespace std;

int main() {
    setlocale(LC_ALL, "rus");
    Field field(true);

    while (!field.isOver()) {
        field.print();
        cout << "Ход " << (field.isRedTurnNow() ? "красных" : "желтых") << ". Введите номер колонки (1-7): ";

        int column;
        if (!(cin >> column)) {
            cin.clear();
            while (cin.get() != '\n');
            continue;
        }

        if (!field.makeTurn(column)) {
            cout << "Некорректный ход! Попробуйте снова."<< endl;
        }
    }

    field.printResult();
    return 0;
}