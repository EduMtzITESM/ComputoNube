#include <iostream>
// Usaré <ctime> para inicializar la semilla aleatoria con srand()
#include <cstdlib>  // Para usar la función rand()
#include <ctime>    // Para usar la función time()
#include <omp.h>

#define N 1000       // Define una constante llamada 'N' con el valor 1000
#define chunk 100    // Define una constante llamada 'chunk' con el valor 100
#define mostrar 10   // Define una constante llamada 'mostrar' con el valor 10

// Toma como argumento un puntero a un número de punto flotante (float *d)
void imprimeArreglo(float *d);

int main()
{
    std::cout << "Estableciendo la cantidad de Hilos!\n";
    float a[N], b[N], c[N]; // Declaración de tres arreglos de tipo float
    // Cada arreglo tiene un tamaño de N elementos
    int i;                  // Declaración de una variable entera

    // Definición de la semilla para la generación los números aleatorios
    srand(time(0));

    // Asignar valores aleatorios entre 0 y 9 para fácil verificación
    for (int i = 0; i < N; i++) 
    {
        // generación de un número aleatorio en el rango a [0, 9]
        a[i] = rand() % 10;
        b[i] = rand() % 10;
    }

    int pedazos = chunk;
    
    // pragma es la directiva de OpenMP que indica que el siguiente ciclo for 
    // se debe ejecutar en paralelo.
    // shared especifica que las variables a, b, c, y pedazos deben ser compartidas entre todos los hilos
    // private(i) indica que la variable i es privada para cada hilo
    // schedule(static, pedazos) define cómo se distribuyen las iteraciones del ciclo entre los hilos
    #pragma omp parallel for \
    shared(a, b, c, pedazos) private (i) \
    schedule(static, pedazos)
    
    for(i = 0; i < N; i++)
    {
        // Se crea el arreglo que es la suma de los arreglos iniciales
        c[i] = a[i] + b[i];
    }

    std::cout << "Imprimiendo los primeros " << mostrar << " valores del arreglo a: " << std::endl;
    imprimeArreglo(a);
    std::cout << "Imprimiendo los primeros " << mostrar << " valores del arreglo b: " << std::endl;
    imprimeArreglo(b);
    std::cout << "Imprimiendo los primeros " << mostrar << " valores del arreglo c: " << std::endl;
    imprimeArreglo(c);
}

// Llamada a 'imprimeArreglo'
// Diseñada para imprimir los primeros elementos (los indicados en la variable 'mostrar')
// de un arreglo de números flotantes 
void imprimeArreglo(float *d)
{
    for (int x = 0; x < mostrar; x++)
    std::cout << d[x] << " - ";
    std::cout << std::endl;
}
