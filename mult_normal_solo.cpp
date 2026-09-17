#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <iomanip>
#include <algorithm>

using namespace std;

double multiplicacion_normal(const vector<double>& A, const vector<double>& B, vector<double>& C, int N) {
    fill(C.begin(), C.end(), 0.0);
    auto inicio = chrono::high_resolution_clock::now();
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            double suma = 0.0;
            for (int k = 0; k < N; k++) {
                suma += A[i * N + k] * B[k * N + j];
            }
            C[i * N + j] = suma;
        }
    }
    auto fin = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duracion = fin - inicio;
    return duracion.count();
}

int main() {
    int N = 500;

    mt19937 generador(42);
    uniform_real_distribution<double> distribucion(0.0, 10.0);

    vector<double> A(N * N), B(N * N), C(N * N, 0.0);
    for (int i = 0; i < N * N; i++) {
        A[i] = distribucion(generador);
        B[i] = distribucion(generador);
    }

    double tiempo = multiplicacion_normal(A, B, C, N);

    cout << "Multiplicacion normal (N = " << N << ")\n";
    cout << "Tiempo: " << tiempo << " ms\n";

    return 0;
}
