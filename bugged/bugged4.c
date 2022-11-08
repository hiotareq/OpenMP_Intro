/******************************************************************************
 * ЗАДАНИЕ: bugged4.c
 * ОПИСАНИЕ:
 *   Очень простая программа параллельных манипуляций с двумерным массивом
 *   зависимо от количества исполнителей... но с segmentation fault.
 ******************************************************************************/

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

#define N 1048

int main(int argc, char *argv[])
{
    int nthreads;

#pragma omp parallel shared(nthreads)
    {
        std::vector<std::vector<double>> a(N, std::vector<double>(N));
        printf("%f", a[0][0]);
        int tid = omp_get_thread_num();
        if (tid == 0)
        {
            nthreads = omp_get_num_threads();
            printf("Number of threads = %d\n", nthreads);
        }
        printf("Thread %d starting...\n", tid);

        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                a[i][j] = tid + i + j;

        printf("Thread %d done. Last element= %f\n", tid, a[N - 1][N - 1]);
    }
}
