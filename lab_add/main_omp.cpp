#include <iostream>
#include <omp.h>
#include <cmath>
#include <vector>
#include <chrono>

size_t ISIZE = 1000, JSIZE = 1000;

int main(int argc, char **argv)
{
    double a[ISIZE][JSIZE];
    int i, j;
    FILE *ff;
    for (i = 0; i < ISIZE; i++)
    {
        for (j = 0; j < JSIZE; j++)
        {
            a[i][j] = 10 * i + j;
        }
    }
    for (i = 0; i < ISIZE - 4; i++)
    {
        for (j = 5; j < JSIZE; j++)
        {
            a[i][j] = sin(0.1 * a[i + 4][j - 5]);
        }
    }
    ff = fopen("result1.txt", "w");
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