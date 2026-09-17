#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <iomanip>
#include <algorithm>

using namespace std;

double multiplicacion_normal(const vector<double>& A,const vector<double>& B,vector<double>& C,int N){
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


double multiplicacion_bloques(const vector<double>& A,const vector<double>& B,vector<double>& C,int N,int tamano_bloque) {
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
                            suma += A[i * N + k] *
                                    B[k * N + j];
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

    vector<int> tamanos = {250, 500, 1000, 2000};
    vector<int> bloques = {8, 16, 32, 64, 128};
    mt19937 generador(42);
    uniform_real_distribution<double> distribucion(0.0, 10.0);

    for (int N : tamanos) {
        cout << "Tamano de matriz N = "<< N << " x " << N << "\n";

        vector<double> A(N * N);
        vector<double> B(N * N);
        vector<double> C(N * N, 0.0);

        for (int i = 0; i < N * N; i++) {
            A[i] = distribucion(generador);
            B[i] = distribucion(generador);
        }

        double tiempo_normal =
            multiplicacion_normal(A, B, C, N);

        cout << "Multiplicacion normal\n";
        cout << "Tiempo: "<< tiempo_normal<< " ms\n";
        cout << endl;
        cout << "Multiplicacion por bloques\n";
        cout << "-----------------------------------------------\n";
        cout << left
             << setw(12) << "Bloque"
             << setw(18) << "Tiempo (ms)"
             << setw(15) << "Speedup"
             << "\n";

        cout << "-----------------------------------------------\n";

        for (int Bsize : bloques) {

            double tiempo_bloques = multiplicacion_bloques(A,B,C,N,Bsize);

            double speedup = tiempo_normal / tiempo_bloques;

            cout << left
                 << setw(12) << Bsize
                 << setw(18) << tiempo_bloques
                 << setw(15) << speedup
                 << "\n";
        }

        cout << "\n";
    }

    return 0;
}