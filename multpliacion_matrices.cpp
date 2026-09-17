#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>

using namespace std;

void multiplicar_matrices_clasico(int n) {
    vector<double> matriz_A(n * n, 1.0);
    vector<double> matriz_B(n * n, 2.0);
    vector<double> matriz_C(n * n, 0.0);

    auto tiempo_inicio = chrono::high_resolution_clock::now();

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            double suma = 0.0;
            for (int k = 0; k < n; k++) {
                suma += matriz_A[i * n + k] * matriz_B[k * n + j];
            }
            matriz_C[i * n + j] = suma;
        }
    }

    auto tiempo_fin = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duracion = tiempo_fin - tiempo_inicio;

    if (matriz_C[0] < 0.0) cout << "";

    cout << setw(8) << n 
         << setw(18) << fixed << setprecision(3) << duracion.count() << "\n";
}

int main() {
    cout << setw(8) << "N" 
         << setw(18) << "Tiempo (ms)\n" ;
    cout << "--------------------------------------------\n";

    vector<int> tamanos = {250, 500, 750, 1000, 1250, 1500, 2000};

    for (int tamano_actual : tamanos) {
        multiplicar_matrices_clasico(tamano_actual);
    }

    return 0;
}