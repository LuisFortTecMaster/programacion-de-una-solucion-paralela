// ------------------------------------------------------------
// SumaArreglosParalela.cpp
//
// Programa que:
// 1) Inicializa dos arreglos de tamaño N con valores aleatorios
// 2) Suma ambos arreglos de forma paralela usando OpenMP
// 3) Utiliza particiones (chunks) de tamaño fijo
// 4) Imprime los primeros valores de cada arreglo para verificación
//
// Autor: Luis Esteban Fortanel Hernández
// ------------------------------------------------------------

#include <iostream>   // Entrada y salida estándar
#include <cstdlib>    // rand(), srand()
#include <ctime>      // time()
#include <omp.h>      // Librería de OpenMP

// --------------------
// Definición de macros
// --------------------

// Tamaño de los arreglos
#define N 1000

// Tamaño de cada partición (chunk) para OpenMP
#define particion 100

// Cantidad de elementos a mostrar por pantalla
#define mostrar 10

// Prototipo de la función que imprime un arreglo
void imprimirArreglo(float* d);

int main()
{
    // Inicializa la semilla del generador de números aleatorios
    srand(time(NULL));

    // Declaración de los arreglos
    float arregloA[N], arregloB[N], arregloC[N];

    int i;

    // --------------------------------------
    // Inicialización secuencial de los arreglos
    // --------------------------------------
    // Se generan valores aleatorios en el rango [0, 100)
    for (int i = 0; i < N; i++) {
        arregloA[i] = (float)rand() / RAND_MAX * 100.0f;
        arregloB[i] = (float)rand() / RAND_MAX * 100.0f;
    }

    // Variable que define el tamaño del chunk
    int particiones = particion;

    // ------------------------------------------------
    // Suma paralela de los arreglos usando OpenMP
    //
    // - parallel for: paraleliza el ciclo for
    // - shared: arreglos compartidos entre hilos
    // - private: cada hilo tiene su propia variable i
    // - schedule(static, particiones):
    //   divide el trabajo en bloques de tamaño fijo
    // ------------------------------------------------
    #pragma omp parallel for \
    shared(arregloA, arregloB, arregloC, particiones) private(i) \
    schedule(static, particiones)
    for (i = 0; i < N; i++) {
        arregloC[i] = arregloA[i] + arregloB[i];
    }

    // --------------------------------------
    // Impresión de resultados (verificación)
    // --------------------------------------
    std::cout << "Imprimiendo los primeros " << mostrar
        << " valores del arreglo A: " << std::endl;
    imprimirArreglo(arregloA);

    std::cout << "Imprimiendo los primeros " << mostrar
        << " valores del arreglo B: " << std::endl;
    imprimirArreglo(arregloB);

    std::cout << "Imprimiendo los primeros " << mostrar
        << " valores del arreglo C: " << std::endl;
    imprimirArreglo(arregloC);

    return 0;
}

// ------------------------------------------------------------
// Función: imprimirArreglo
// Recibe un arreglo de tipo float y muestra los primeros
// "mostrar" elementos en pantalla
// ------------------------------------------------------------
void imprimirArreglo(float* d)
{
    for (int x = 0; x < mostrar; x++) {
        std::cout << d[x] << " - ";
    }
    std::cout << std::endl;
}
