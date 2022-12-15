#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <mpi.h>

#define ISIZE 5000
#define JSIZE 5000
double a[ISIZE][JSIZE];

int main(int argc, char **argv)
{
    int i, j;
    FILE *ff;

    int commsize, rank;

    // подготовительная часть – заполнение некими данными
    for (i = 0; i < ISIZE; i++)
    {
        for (j = 0; j < JSIZE; j++)
        {
            a[i][j] = 10 * i + j;
        }
    }

    // initialising MPI
    MPI_Init(&argc, &argv);
    // get number of processes
    MPI_Comm_size(MPI_COMM_WORLD, &commsize);

    // get rank of current process
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int sizes[commsize];
    int tsize = JSIZE / commsize;
    int start_elem = rank * tsize;
    int end_elem = (rank == commsize - 1) ? JSIZE : start_elem + tsize;

    int size = end_elem - start_elem;

    if (rank == 0)
        for (int i = 0; i < commsize; i++)
            sizes[i] = (i == commsize - 1) ? JSIZE - i * tsize : tsize;

    double start = MPI_Wtime();

    // требуется обеспечить измерение времени работы данного цикла
    for (i = 0; i < ISIZE; ++i)
    {
        for (j = start_elem; j < end_elem; ++j)
        {
            a[i][j] = sin(2 * a[i][j]);
        }
    }

    if (rank != 0)
        for (int i = 0; i < ISIZE; i++)
        {
            MPI_Send(&(a[i][start_elem]), size, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
        }
    if (rank == 0)
        for (int j = 1; j < commsize; j++)
            for (int i = 0; i < ISIZE; i++)
            {
                MPI_Recv(&(a[i][j * tsize]), sizes[j], MPI_DOUBLE, j, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            }

    double time = MPI_Wtime() - start;
    if (rank == 0)
        std::cout << commsize << " " << time << std::endl;

    if (rank == 0)
    {
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

    MPI_Finalize();
    return 0;
}