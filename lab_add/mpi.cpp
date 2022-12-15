#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <math.h>
#include <mpi.h>

#define ISIZE 5000
#define JSIZE ISIZE
double a[ISIZE][JSIZE];

// вектор расстояний (3, -2), вектор направлений (<, >), это истинная зависимость => распараллельвание по внутреннему циклу с синхронизацией по внешней итерации

int main(int argc, char *argv[])
{

    int commsize, rank;

    for (int i = 0; i < ISIZE; i++)
        for (int j = 0; j < JSIZE; j++)
        {
            a[i][j] = 10 * i + j;
        }

    // initialising MPI
    MPI_Init(&argc, &argv);
    // get number of processes
    MPI_Comm_size(MPI_COMM_WORLD, &commsize);

    // get rank of current process
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int sizes[commsize];
    int segment_size = (JSIZE - 1) / commsize;
    int start_elem = rank * segment_size;
    int end_elem = (rank == commsize - 1) ? JSIZE - 1 : start_elem + segment_size;

    int size = end_elem - start_elem;

    if (rank == 0)
        for (int i = 0; i < commsize; i++)
            sizes[i] = (i == commsize - 1) ? JSIZE - 1 - i * segment_size : segment_size;

    double start = MPI_Wtime();

    for (int i = 1; i < ISIZE; ++i)
    {
        for (int j = start_elem; j < end_elem; ++j)
        {
            a[i][j] = sin(2 * a[i - 1][j + 1]);
        }

        if (rank != 0)
        {
            MPI_Send(&(a[i][start_elem]), 1, MPI_DOUBLE, rank - 1, 0, MPI_COMM_WORLD);
        }
        if (rank != commsize - 1)
        {
            MPI_Recv(&(a[i][end_elem]), 1, MPI_DOUBLE, rank + 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }
    }

    if (rank != 0)
        for (int i = 1; i < ISIZE; i++)
        {
            MPI_Send(&(a[i][start_elem]), size, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
        }
    if (rank == 0)
        for (int j = 1; j < commsize; j++)
            for (int i = 1; i < ISIZE; i++)
            {
                MPI_Recv(&(a[i][j * segment_size]), sizes[j], MPI_DOUBLE, j, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            }

    double time = MPI_Wtime() - start;
    if (rank == 0)
        std::cout << commsize << " " << time << std::endl;

    if (rank == 0)
    {
        FILE *ff;
        ff = fopen("result3.txt", "w");
        for (int i = 0; i < ISIZE; i++)
        {
            for (int j = 0; j < JSIZE; j++)
            {
                fprintf(ff, "%f ", a[i][j]);
            }
            fprintf(ff, "\n");
        }
        fclose(ff);
    }

    // end of parallel region
    MPI_Finalize();
    return 0;
}

// mpicxx mpi.cpp -o mpi
// mpirun  -np 4 mpi
// --mca opal_warn_on_missing_libcuda 0