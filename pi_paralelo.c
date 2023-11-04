#include <stdio.h>
#include <omp.h>
#include <time.h>

static long num_steps = 100000;
double step;
#define NUM_THREADS 2

int main() {
    double pi;
    step = 1.0 / (double)num_steps;
    omp_set_num_threads(NUM_THREADS);

    clock_t start_time = clock(); // Registrar el tiempo de inicio

    #pragma omp parallel
    {
        int i, id, nthrds;
        double x, sum;
        id = omp_get_thread_num();
        nthrds = omp_get_num_threads();
        if (id == 0) nthrds = nthrds;

        for (i = id, sum = 0.0; i < num_steps; i = i + nthrds) {
            x = (i + 0.5) * step;
            sum += 4.0 / (1.0 + x * x);
        }

        #pragma omp critical
        pi += sum * step;
    }

    clock_t end_time = clock(); // Registrar el tiempo de finalización
    double execution_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    printf("Valor de Pi: %lf\n", pi);
    printf("Tiempo de ejecucion: %lf segundos\n", execution_time);

    return 0;
}
