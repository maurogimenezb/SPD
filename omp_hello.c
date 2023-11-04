#include "omp.h"
#include "stdio.h"

int main()
{

    int total1, total2, total3, total4 = 0;
#pragma omp parallel num_threads(4) 
    {
        int sumaParcial = 0;
        int ID = omp_get_thread_num();
        /* printf("hello (%d)", ID);
        printf("world (%d)\n", ID); */
        if(ID == 0){
            sumaParcial += 1;
            total1 = sumaParcial;
        }
        if(ID == 1){
            sumaParcial += 2;
            total2 = sumaParcial;
        }
        if(ID == 2){
            sumaParcial += 3;
            total3 = sumaParcial;
        }
        if(ID == 3){
            sumaParcial += 4;
            total4 = sumaParcial;
        }
    }
    printf("total= %d \n", total1 + total2 + total3 + total4 );
    return 0;
}