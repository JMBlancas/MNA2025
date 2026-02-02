// TAREA.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <omp.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>
// Se generan los arreglos A y B con números aleatorios entre 1 y 1000.
int main() {
    const int N = 1000;

    std::vector<int> A(N);
    std::vector<int> B(N);
    std::vector<int> R(N);
    // Con time se crea la semilla de aleatoriedad de los números
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    for (int i = 0; i < N; ++i) {
        A[i] = std::rand() % 1000 + 1;
        B[i] = std::rand() % 1000 + 1;
    }
	// Se genera la suma de los arreglos A y B en R usando OpenMP
#pragma omp parallel
    {
        int thread_id = omp_get_thread_num();

#pragma omp for
        for (int i = 0; i < N; ++i) {
            R[i] = A[i] + B[i];

			// Simula tiempos distintos por hilo con el fin de mostrar gráficamente la concurrencia y el cómo actúan de manera individual (deja unos en reposo más tiempo que otros).
            std::this_thread::sleep_for(
                std::chrono::milliseconds(5 * (thread_id + 1))
            );
        }
		// Se genera una sección crítica para que no se mezclen las salidas de los hilos
#pragma omp critical
        {
            std::cout << "Hilo " << thread_id << " TERMINÓ su trabajo"
                << std::endl;
        }
    }
	// Se muestran los primeros 20 resultados de la suma
    std::cout << "\nPrimeros resultados:\nR: ";
    for (int i = 0; i < 20; ++i) std::cout << R[i] << " ";
    std::cout << std::endl;

    return 0;
}