#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <locale.h>
#include "datetime.h"
#include "array.h"

using namespace std;

int abs(int n) {
    return (n < 0) ? -n : n;
}

int main() {
    setlocale(LC_ALL, "rus");

    string input;
    cout << "Введите дату (дд-мм-гггг): ";
    cin >> input;

    int d, m, y;
    char sep;
    istringstream din(input);
    if (!(din >> d >> sep >> m >> sep >> y)) {
        cerr << "Ошибка формата." << endl;
        return 1;
    }

    try {
        DateTime test(y, m, d);
    }
    catch (...) {
        cerr << "Некорректная дата." << endl;
        return -1;
    }

    ostringstream fnameStream;
    fnameStream << "moon" << y << ".dat";
    ifstream fin(fnameStream.str());
    if (!fin.is_open()) return -1;

    string header;
    getline(fin, header);

    Array elevations;
    Array timesHMS;

    long long currentYMD;
    int hms;
    double t, r, el, az, fi, lg;

    int targetYMD = y * 10000 + m * 100 + d;
    int maxEl = -999999;
    int maxTimeHMS = 0;

    while (fin >> currentYMD >> hms >> t >> r >> el >> az >> fi >> lg) {
        if (currentYMD == targetYMD) {
            int eInt = (int)(el * 1000);
            elevations.insert(eInt);
            timesHMS.insert(hms);

            if (eInt > maxEl) {
                maxEl = eInt;
                maxTimeHMS = hms;
            }
        }
        else if (currentYMD > targetYMD) break;
    }
    fin.close();

    if (elevations.getSize() == 0) {
        cout << "Данных на эту дату нет." << endl;
        return 0;
    }

    DateTime displayDate(y, m, d);
    int dummyY, dummyM, dummyD;
    displayDate.getDate(dummyY, dummyM, dummyD);

    cout << "Дата: " << (dummyD < 10 ? "0" : "") << dummyD << "." << (dummyM < 10 ? "0" : "") << dummyM << "." << dummyY << endl;

    for (int i = 0; i < elevations.getSize(); ++i) {
        int h = timesHMS[i] / 10000;
        int min = (timesHMS[i] / 100) % 100;
        int s = timesHMS[i] % 100;

        DateTime currentDT(y, m, d, h, min, s);

        if (i > 0 && elevations[i - 1] < 0 && elevations[i] >= 0) {
            int hh, mm, ss;
            currentDT.getTime(hh, mm, ss);
            cout << "Восход Луны: " << currentDT << endl;
        }

        if (timesHMS[i] == maxTimeHMS) {
            cout << "Кульминация Луны: " << currentDT << endl;
        }

        if (i > 0 && elevations[i - 1] > 0 && elevations[i] <= 0) {
            cout << "Заход Луны: " << currentDT << endl;
        }
    }

    return 0;
}