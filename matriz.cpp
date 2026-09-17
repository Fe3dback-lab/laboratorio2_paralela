#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>

using namespace std;

void comparaciones(int MAX) {
    vector<double> A(MAX * MAX, 1.0);
    vector<double> x(MAX, 2.0);
    vector<double> y1(MAX, 0.0);
    vector<double> y2(MAX, 0.0);

    // bucle 1
    auto inicio1 = chrono::high_resolution_clock::now();
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            y1[i] += A[i * MAX + j] * x[j];
        }
    }
    auto fin1 = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> tiempo1 = fin1 - inicio1;

    // bucle 2
    auto inicio2 = chrono::high_resolution_clock::now();
    for (int j = 0; j < MAX; j++) {
        for (int i = 0; i < MAX; i++) {
            y2[i] += A[i * MAX + j] * x[j];
        }
    }
    auto fin2 = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> tiempo2 = fin2 - inicio2;

    cout << setw(8) << MAX 
         << setw(16) << tiempo1.count() 
         << setw(16) << tiempo2.count() 
         << setw(12) << (tiempo2.count() / tiempo1.count()) << "\n";
}

int main() {
    cout << setw(8) << "MAX" 
         << setw(16) << "Bucle 1 (ms)" 
         << setw(16) << "Bucle 2 (ms)" 
         << setw(12) << "Speedup\n";
    cout << "----------------------------------------------------\n";

    vector<int> tam = {1000, 2000, 4000, 8000, 12000, 16000};
    for (int i : tam) {
        comparaciones(i);
    }
    return 0;
}
