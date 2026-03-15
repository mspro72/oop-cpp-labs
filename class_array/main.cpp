#include <iostream>
#include <locale.h>
#include <ctime>
#include "array.h"
using namespace std;

int Joseb(int n, int k) {
    Array arr(n);
    for (int i = 0; i < n; i++)
        arr.insert(i+1);

    int j = 0;
    while (arr.getSize() > 1) {
        j = (j + k - 1) % arr.getSize();
        arr.remove(j);
    }
    return arr[0];
}

int main(void) {
    setlocale(LC_ALL, "Russian");
    clock_t start;
    int result;

    start = clock();
    result = Joseb(13, 3);
    cout << "n=13" << " Ответ: " << result << " Время: " << (double)(clock() - start) / CLOCKS_PER_SEC * 1000 << " мс" << endl;

    start = clock();
    result = Joseb(100, 2);
    cout << "n=100" << " Ответ: " << result << " Время: " << (double)(clock() - start) / CLOCKS_PER_SEC * 1000 << " мс" << endl;

    start = clock();
    result = Joseb(1000, 2);
    cout << "n=1000" << " Ответ: " << result << " Время: " << (double)(clock() - start) / CLOCKS_PER_SEC * 1000 << " мс" << endl;

    start = clock();
    result = Joseb(5000, 2);
    cout << "n=5000" << " Ответ: " << result << " Время: " << (double)(clock() - start) / CLOCKS_PER_SEC * 1000 << " мс" << endl;

    start = clock();
    result = Joseb(10000, 2);
    cout << "n=10000" << " Ответ: " << result << " Время: " << (double)(clock() - start) / CLOCKS_PER_SEC * 1000 << " мс" << endl;

    start = clock();
    result = Joseb(50000, 2);
    cout << "n=50000" << " Ответ: " << result << " Время: " << (double)(clock() - start) / CLOCKS_PER_SEC * 1000 << " мс" << endl;

    start = clock();
    result = Joseb(100000, 2);
    cout << "n=100000" << " Ответ: " << result << " Время: " << (double)(clock() - start) / CLOCKS_PER_SEC * 1000 << " мс" << endl;

    start = clock();
    result = Joseb(500000, 2);
    cout << "n=500000" << " Ответ: " << result << " Время: " << (double)(clock() - start) / CLOCKS_PER_SEC * 1000 << " мс" << endl;

    start = clock();
    result = Joseb(1000000, 2);
    cout << "n=1000000" << " Ответ: " << result << " Время: " << (double)(clock() - start) / CLOCKS_PER_SEC * 1000 << " мс" << endl;

    return 0;
}