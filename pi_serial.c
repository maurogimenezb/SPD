#include <stdio.h>
#include <time.h>

static long num_steps = 100000;
double step;

int main() {
    int i;
    double x, pi, sum = 0.0;
    step = 1.0 / (double)num_steps;

    clock_t start_time = clock(); // Registrar el tiempo de inicio

    for (i = 0; i < num_steps; i++) {
        x = (i + 0.5) * step;
        sum = sum + 4.0 / (1.0 + x * x);
    }

    pi = step * sum;

    clock_t end_time = clock(); // Registrar el tiempo de finalización

    double execution_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    printf("Valor de Pi: %lf\n", pi);
    printf("Tiempo de ejecucion: %lf segundos\n", execution_time);

    return 0;
}
