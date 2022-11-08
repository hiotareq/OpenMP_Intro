/******************************************************************************
 * ЗАДАНИЕ: bugged2.c
 * ОПИСАНИЕ:
 *   Еще одна программа на OpenMP с багом.
 *   Программа демонстрирует возможности динамического распределения нагрузки
 *   при вычислении суммы элементов арифметической прогрессии.
 ******************************************************************************/

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    int nthreads, i, tid;
    float total = 0.0, local = 0.0;

#pragma omp parallel shared(total) private(local,tid)
    {
        tid = omp_get_thread_num();
        if (tid == 0)
        {
            nthreads = omp_get_num_threads();
            printf("Number of threads = %d\n", nthreads);
        }
#pragma omp barrier

        printf("Thread %d is starting...\n", tid);

#pragma omp for schedule(dynamic, 10)
        for (i = 0; i < 1000000; i++)
            local = local + i * 1.0;

        printf("Thread %d is done! Local= %e\n", tid, local);

#pragma omp critical
        total += local;
    }

    printf("Total = %e\n", total);
}
