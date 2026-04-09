#include <iostream>
#include <locale.h>
#include <windows.h>
#include "linelist.h"
using namespace std;

int Joseb(int n, int k) {
    LineList<int> list;

    for (int i = n; i >= 1; i--)
        list.insertFirst(i);

    LineListElem<int>* cur = list.getStart();
    LineListElem<int>* prev = nullptr;

    auto getLast = [&]() {
        LineListElem<int>* p = list.getStart();
        while (p->getNext()) p = p->getNext();
        return p;
        };

    while (list.getStart()->getNext() != nullptr) {
        for (int i = 0; i < k - 1; i++) {
            prev = cur;
            if (cur->getNext())
                cur = cur->getNext();
            else {
                prev = getLast();
                cur = list.getStart();
            }
        }

        LineListElem<int>* next;
        if (cur->getNext())
            next = cur->getNext();
        else
            next = list.getStart();

        if (cur == list.getStart()) {
            list.deleteFirst();
        }
        else {
            list.deleteAfter(prev);
        }

        cur = next;
        if (cur == nullptr)
            cur = list.getStart();
    }

    return list.getStart()->getData();
}

int main(void) {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    SetConsoleOutputCP(65001);  // исправление кодировки для Windows

    clock_t start;
    int result;

    start = clock();
    result = Joseb(13, 3);
    cout << "n=13      | Answer: " << result << " | Time: " << (double)(clock() - start) / CLOCKS_PER_SEC * 1000 << " ms" << endl;

    start = clock();
    result = Joseb(100, 2);
    cout << "n=100     | Answer: " << result << " | Time: " << (double)(clock() - start) / CLOCKS_PER_SEC * 1000 << " ms" << endl;

    start = clock();
    result = Joseb(1000, 2);
    cout << "n=1000    | Answer: " << result << " | Time: " << (double)(clock() - start) / CLOCKS_PER_SEC * 1000 << " ms" << endl;

    start = clock();
    result = Joseb(5000, 2);
    cout << "n=5000    | Answer: " << result << " | Time: " << (double)(clock() - start) / CLOCKS_PER_SEC * 1000 << " ms" << endl;

    start = clock();
    result = Joseb(10000, 2);
    cout << "n=10000   | Answer: " << result << " | Time: " << (double)(clock() - start) / CLOCKS_PER_SEC * 1000 << " ms" << endl;

    start = clock();
    result = Joseb(50000, 2);
    cout << "n=50000   | Answer: " << result << " | Time: " << (double)(clock() - start) / CLOCKS_PER_SEC * 1000 << " ms" << endl;

    start = clock();
    result = Joseb(100000, 2);
    cout << "n=100000  | Answer: " << result << " | Time: " << (double)(clock() - start) / CLOCKS_PER_SEC * 1000 << " ms" << endl;

    start = clock();
    result = Joseb(500000, 2);
    cout << "n=500000  | Answer: " << result << " | Time: " << (double)(clock() - start) / CLOCKS_PER_SEC * 1000 << " ms" << endl;

    start = clock();
    result = Joseb(1000000, 2);
    cout << "n=1000000 | Answer: " << result << " | Time: " << (double)(clock() - start) / CLOCKS_PER_SEC * 1000 << " ms" << endl;

    return 0;
}
