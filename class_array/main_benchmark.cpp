#include <iostream>
#include <fstream>
#include <ctime>
#include "array.h"
using namespace std;

int Joseb(int n, int k) {
    Array arr(n);
    for (int i = 0; i < n; i++)
        arr.insert(i + 1);

    int j = 0;
    while (arr.getSize() > 1) {
        j = (j + k - 1) % arr.getSize();
        arr.remove(j);
    }
    return arr[0];
}

int main(void) {
    ofstream csv("results.csv");
    csv << "n,time_sec" << endl;

    // Phase 1: from 1000 to 100000, step 1000
    for (int n = 1000; n <= 100000; n += 1000) {
        clock_t start = clock();
        int result = Joseb(n, 2);
        double elapsed = (double)(clock() - start) / CLOCKS_PER_SEC;

        cout << "n=" << n << "  result=" << result
             << "  time=" << elapsed << " sec" << endl;
        csv << n << "," << elapsed << endl;
    }

    // Phase 2: from 120000 to 1280000, step 20000
    for (int n = 110000; n <= 1280000; n += 10000) {
        clock_t start = clock();
        int result = Joseb(n, 2);
        double elapsed = (double)(clock() - start) / CLOCKS_PER_SEC;

        cout << "n=" << n << "  result=" << result
             << "  time=" << elapsed << " sec" << endl;
        csv << n << "," << elapsed << endl;
    }

    csv.close();
    cout << "\nDone! Results saved to results.csv" << endl;
    return 0;
}
