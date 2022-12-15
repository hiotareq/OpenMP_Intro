#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <vector>
#include <omp.h>
#include <iostream>

#define ISIZE 5000
#define JSIZE 5000

int main(int argc, char **argv)
{
    std::vector<std::vector<double>> a(ISIZE, std::vector<double>(JSIZE));
    int i, j;
    FILE *ff;
    // подготовительная часть – заполнение некими данными
    for (i = 0; i < ISIZE; i++)
    {
        for (j = 0; j < JSIZE; j++)
        {
            a[i][j] = 10 * i + j;
        }
    }

    double start_time, end_time;
// требуется обеспечить измерение времени работы данного цикла
#pragma omp parallel shared(a, start_time, end_time)
    {
        start_time = omp_get_wtime();
#pragma omp for schedule(dynamic, 1000)
        for (i = 0; i < ISIZE; i++)
        {
            for (j = 0; j < JSIZE; j++)
            {
                a[i][j] = sin(2 * a[i][j]);
            }
        }
        end_time = omp_get_wtime();
    }
    std::cout << end_time - start_time << std::endl;
    ff = fopen("result.txt", "w");
    for (i = 0; i < ISIZE; i++)
    {
        for (j = 0; j < JSIZE; j++)
        {
            fprintf(ff, "%f ", a[i][j]);
        }
        fprintf(ff, "\n");
    }
    fclose(ff);
}