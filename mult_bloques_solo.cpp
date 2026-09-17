#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <iomanip>
#include <algorithm>

using namespace std;

double multiplicacion_bloques(const vector<double>& A, const vector<double>& B, vector<double>& C, int N, int tamano_bloque) {
    fill(C.begin(), C.end(), 0.0);
    auto inicio = chrono::high_resolution_clock::now();
    for (int ii = 0; ii < N; ii += tamano_bloque) {
        for (int jj = 0; jj < N; jj += tamano_bloque) {
            for (int kk = 0; kk < N; kk += tamano_bloque) {

                int limite_i = min(ii + tamano_bloque, N);
                int limite_j = min(jj + tamano_bloque, N);
                int limite_k = min(kk + tamano_bloque, N);

                for (int i = ii; i < limite_i; i++) {
                    for (int j = jj; j < limite_j; j++) {
                        double suma = C[i * N + j];
                        for (int k = kk; k < limite_k; k++) {
                            suma += A[i * N + k] * B[k * N + j];
                        }
                        C[i * N + j] = suma;
                    }
                }
            }
        }
    }
    auto fin = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duracion = fin - inicio;
    return duracion.count();
}

int main() {
    int N = 500;
    int Bsize = 64;
    mt19937 generador(42);
    uniform_real_distribution<double> distribucion(0.0, 10.0);

    vector<double> A(N * N), B(N * N), C(N * N, 0.0);
    for (int i = 0; i < N * N; i++) {
        A[i] = distribucion(generador);
        B[i] = distribucion(generador);
    }

    double tiempo = multiplicacion_bloques(A, B, C, N, Bsize);

    cout << "Multiplicacion por bloques (N = " << N << ", bloque = " << Bsize << ")\n";
    cout << "Tiempo: " << tiempo << " ms\n";

    return 0;
}
