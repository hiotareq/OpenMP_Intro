#include <iostream>
#include <omp.h>
#include <cmath>
#include <vector>
#include <chrono>

size_t ISIZE = 1000, JSIZE = 1000;

// вектор расстояний (-4, 5), вектор направлений (>, <), это антизависимость => распараллельвание по внешнему циклу с дублированием входных данных

int main(int argc, char **argv)
{
    // dynamic vector instead of static C-like array because OpenMP has some problems with huge static amounts of data
    std::vector<std::vector<double>> a(ISIZE, std::vector<double>(JSIZE));

    // matrix where put values from second  for-loop
    std::vector<std::vector<double>> copy(ISIZE, std::vector<double>(JSIZE));

    FILE *ff;

    double start_time, end_time;
// begining of parallel region
#pragma omp parallel shared(a, copy, start_time, end_time)
    {
#pragma omp for schedule(guided)
        for (size_t i = 0; i < ISIZE; i++)
        {
            for (size_t j = 0; j < JSIZE; j++)
            {
                a[i][j] = 10 * i + j;
                copy[i][j] = a[i][j];
            }
        }

// barrier for processe and not beginning second loop too early
#pragma omp barrier
#pragma omp master
        {
            start_time = omp_get_wtime();
        }

#pragma omp for schedule(static, 1)
        for (size_t i = 0; i < ISIZE - 4; i++)
        {
            for (size_t j = 5; j < JSIZE; j++)
            {
                copy[i][j] = sin(0.1 * a[i + 4][j - 5]);
            }
        }

#pragma omp master
        {
            end_time = omp_get_wtime();
            std::cout << omp_get_num_threads() << std::endl;
        }
    }
    // end of parallel region

    // work with file is not parallelised because this simple operation in C is good enough even for big amounts of data and it makes no sense to parallel it
    ff = fopen("result.txt", "w");

    for (size_t i = 0; i < ISIZE; i++)
    {
        for (size_t j = 0; j < JSIZE; j++)
            fprintf(ff, "%f ", copy[i][j]);
        fprintf(ff, "\n");
    }

    fclose(ff);

    std::cout << end_time - start_time << std::endl;

    return 0;
}

// g++ -fopenmp omp.cpp -o omp
// OMP_NUM_THREADS=4 ./omp