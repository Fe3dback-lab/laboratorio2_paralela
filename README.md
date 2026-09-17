# laboratorio2_paralela

Este repositorio cotiene los codigos solicitados para las actividades del Laboratorio 2 del curso de Computacion Paralela y Distribuida
## Requisitos

- Compilador **g++** con soporte para C++17.
-  **Valgrind** con la herramienta **Cachegrind**, y **KCachegrind** para visualizar los resultados:
  ```bash
  sudo apt update
  sudo apt install valgrind kcachegrind g++
  ```
## Compilación y ejecución

Cada codigo tiene que ser ejecutado de forma independiente, cada uno resuelve una actividad de la practica de laboratorio asignada
**Compilación archivos matriz.cpp, multipliacion_matrices.cpp (implementacion clasica de la multiplicacion de matrices) y matriz_bolques.cpp (que realiza la multiplicacion de matrices por bloques y la compara con la multipliacion clasica):**
```bash
g++ matriz.cpp -o matriz
./matriz

g++ multipliacion_matrices.cpp -o multiplicacion_matrices
./multiplicacion_matrices

g++ matriz_bolques.cpp -o matriz_bolques
./matriz_bolques
```
Cada programa imprime en consola los tiempos de ejecución para los distintos tamaños de entrada definidos dentro del codigo, en el caso de el codigo matriz_bolques.cpp, imprime tambien el tamños del bloque con el que se realiza la multiplicacion:
**Compilación para análisis con Valgrind/Cachegrind:**
```bash
g++ -g -O0 -o mult_normal_solo mult_normal_solo.cpp
g++ -g -O0 -o mult_bloques_solo mult_bloques_solo.cpp
```
Se usa `-O0 -g` para que el análisis refleje el algoritmo tal cual está escrito y para que Cachegrind pueda mostrar el costo línea por línea del código fuente.

```bash
valgrind --tool=cachegrind --cachegrind-out-file=clasica.out ./mult_normal_solo
valgrind --tool=cachegrind --cachegrind-out-file=bloques.out ./mult_bloques_solo
```

Al terminar, la terminal imprime un resumen con instrucciones ejecutadas, accesos a memoria y fallos de cache. Si se quiere una opcion mas visual usando KCachegrind, luego de ejecutar los comandos anteriores ejecutar los siguientes:

```bash
kcachegrind clasica.out
kcachegrind bloques.out
```