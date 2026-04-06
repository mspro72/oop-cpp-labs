#include <iostream>
#include <fstream>
#include <ctime>
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
    ofstream csv("benchmark.csv");
    csv << "n,time_ms" << endl;

    clock_t start;
    int result;

    for (int n = 1000; n <= 100000; n += 1000) {
        start = clock();
        result = Joseb(n, 2);
        double time_ms = (double)(clock() - start) / CLOCKS_PER_SEC * 1000;
        csv << n << "," << time_ms << endl;
        cout << "n=" << n << " | Time: " << time_ms << " ms" << endl;

    }
    for (int n = 110000; n <= 1000000; n += 10000) {
        start = clock();
        result = Joseb(n, 2);
        double time_ms = (double)(clock() - start) / CLOCKS_PER_SEC * 1000;
        csv << n << "," << time_ms << endl;
        cout << "n=" << n << " | Time: " << time_ms << " ms" << endl;
    }

    csv.close();
    cout << "Saved to benchmark.csv" << endl;

    return 0;
}
