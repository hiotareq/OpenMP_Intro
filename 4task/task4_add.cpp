#include <iostream>
#include <omp.h>
#include <random>
#include <bits/stdc++.h>
#include <vector>
#include <chrono>

/*
stages of development of the algorithm:
    1. Single threaded algo
    2. Signed-threaded with dot product
    3. Parallel same algo
    4. Parallel with using dot product
    5. Parallel with using transposed martix B
    6. Stage 3 and stage 4 together
*/

// Simple single-threaded multiplication of 2 matrices
void SingleThreadedMultiplication(unsigned long long **A, unsigned long long **B, unsigned long long **OUT, size_t SIZE)
{
    auto start = std::chrono::high_resolution_clock::now();

    for (size_t i = 0; i < SIZE; ++i)
        for (size_t j = 0; j < SIZE; ++j)
            for (size_t k = 0; k < SIZE; ++k)
                OUT[i][j] += A[i][k] * B[k][j];

    auto stop = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

    printf("Single-threaded algo's elapsed time for size %d is %d milliseconds\n", SIZE, duration.count());
}

// Single-threaded multiplication of 2 matrices with using dot product to increase performance by not using pointers to OUT matrix
void SingleThreadedMultiplicationWithdotproduct(unsigned long long **A, unsigned long long **B, unsigned long long **OUT, size_t SIZE)
{
    auto start = std::chrono::high_resolution_clock::now();

    for (size_t i = 0; i < SIZE; ++i)
        for (size_t j = 0; j < SIZE; ++j)
        {
            unsigned long long dot = 0;
            for (size_t k = 0; k < SIZE; ++k)
            {
                dot += A[i][k] * B[k][j];
            }
            OUT[i][j] = dot;
        }

    auto stop = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

    printf("Single-threaded algo's with dot product for size %d elapsed time is %d milliseconds\n", SIZE, duration.count());
}

// Single threaded multiplication with using dot product to increase performance and using transposed B matrix to inctrease number of cache-hits
void SingleThreadedMultiplicationWithTransposeAndDot(unsigned long long **A, unsigned long long **B, unsigned long long **OUT, size_t SIZE)
{
    // transpose B
    unsigned long long **BT = new unsigned long long *[SIZE];
    for (size_t i = 0; i < SIZE; i++)
        BT[i] = new unsigned long long[SIZE];

    for (size_t i = 0; i < SIZE; ++i)
        for (size_t j = 0; j < SIZE; ++j)
            BT[j][i] = B[i][j];

    auto start = std::chrono::high_resolution_clock::now();

    for (size_t i = 0; i < SIZE; ++i)
        for (size_t j = 0; j < SIZE; ++j)
        {
            unsigned long long dot = 0;
            for (size_t k = 0; k < SIZE; ++k)
            {
                dot += A[i][k] * BT[j][k];
            }
            OUT[i][j] = dot;
        }

    auto stop = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

    printf("Single-threaded algo's with dot product and transposed B for size %d elapsed time is %d milliseconds\n", SIZE, duration.count());

    for (size_t i = 0; i < SIZE; i++)
        delete[] BT[i];
    delete[] BT;
}

// Same as single-threaded algo but done in parallel without any optimization
void ParallelMultiplication(unsigned long long **A, unsigned long long **B, unsigned long long **OUT, size_t SIZE)
{
    auto start = std::chrono::high_resolution_clock::now();

#pragma omp parallel shared(A, B, OUT)
    {
#pragma omp for
        for (size_t i = 0; i < SIZE; ++i)
            for (size_t j = 0; j < SIZE; ++j)
                for (size_t k = 0; k < SIZE; ++k)
                    OUT[i][j] += A[i][k] * B[k][j];
    }

    auto stop = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

    printf("Parallel algo for size %d elapsed time is %d milliseconds\n", SIZE, duration.count());
}

// Parallel algo with implemented dot product to not use pointers to OUT matrix
void ParallelMultiplicationWithdotptoduct(unsigned long long **A, unsigned long long **B, unsigned long long **OUT, size_t SIZE)
{
    auto start = std::chrono::high_resolution_clock::now();

#pragma omp parallel shared(A, B, OUT)
    {
#pragma omp for
        for (size_t i = 0; i < SIZE; ++i)
            for (size_t j = 0; j < SIZE; ++j)
            {
                unsigned long long dot = 0;
                for (size_t k = 0; k < SIZE; ++k)
                {
                    dot += A[i][k] * B[k][j];
                }
                OUT[i][j] = dot;
            }
    }

    auto stop = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

    printf("Parallel algo with dot product for size %d elapsed time is %d milliseconds\n", SIZE, duration.count());
}

// Using transposed matrix to understand that this optimization is not as good for parallel algo
void ParallelMultiplicationWithtransposedB(unsigned long long **A, unsigned long long **B, unsigned long long **OUT, size_t SIZE)
{
    // transpose B
    unsigned long long **BT = new unsigned long long *[SIZE];
    for (size_t i = 0; i < SIZE; i++)
        BT[i] = new unsigned long long[SIZE];

    for (size_t i = 0; i < SIZE; ++i)
        for (size_t j = 0; j < SIZE; ++j)
            BT[j][i] = B[i][j];

    auto start = std::chrono::high_resolution_clock::now();

#pragma omp parallel shared(A, BT, OUT)
    {
#pragma omp for
        for (size_t i = 0; i < SIZE; ++i)
            for (size_t j = 0; j < SIZE; ++j)
                for (size_t k = 0; k < SIZE; ++k)
                    OUT[i][j] += A[i][k] * BT[j][k];
    }

    auto stop = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

    printf("Parallel algo with transposed B matrix for size %d elapsed time is %d milliseconds\n", SIZE, duration.count());

    for (size_t i = 0; i < SIZE; i++)
        delete[] BT[i];
    delete[] BT;
}

// parallel algo using dot product and transposed matrix together to get max performance
void ParallelMultiplicationMaxPerformance(unsigned long long **A, unsigned long long **B, unsigned long long **OUT, size_t SIZE)
{
    // transpose B
    unsigned long long **BT = new unsigned long long *[SIZE];
    for (size_t i = 0; i < SIZE; i++)
        BT[i] = new unsigned long long[SIZE];

    for (size_t i = 0; i < SIZE; ++i)
        for (size_t j = 0; j < SIZE; ++j)
            BT[j][i] = B[i][j];

    auto start = std::chrono::high_resolution_clock::now();

#pragma omp parallel shared(A, BT, OUT)
    {
#pragma omp for schedule(dynamic, 1)
        for (size_t i = 0; i < SIZE; ++i)
            for (size_t j = 0; j < SIZE; ++j)
            {
                unsigned long long dot = 0;
                for (size_t k = 0; k < SIZE; ++k)
                {
                    dot += A[i][k] * BT[j][k];
                }
                OUT[i][j] = dot;
            }
    }

    auto stop = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

    printf("Parallel algo with max performance for size %d elapsed time is %d milliseconds\n", SIZE, duration.count());

    for (size_t i = 0; i < SIZE; i++)
        delete[] BT[i];
    delete[] BT;
}

int main(int argc, char *argv[])
{
    // define size of our quadratic matrices
    size_t SIZE = 1000;

    // define matrices A,B to be multiplied and OUT - result of their multiplication
    unsigned long long **A = new unsigned long long *[SIZE];
    unsigned long long **B = new unsigned long long *[SIZE];
    unsigned long long **OUT = new unsigned long long *[SIZE];
    for (size_t i = 0; i < SIZE; i++)
    {
        A[i] = new unsigned long long[SIZE];
        B[i] = new unsigned long long[SIZE];
        OUT[i] = new unsigned long long[SIZE];
    }

    // fiil matrices with initial values
    for (size_t i = 0; i < SIZE; i++)
        for (size_t j = 0; j < SIZE; j++)
        {
            A[i][j] = i;
            B[i][j] = j;
            OUT[i][j] = 0;
        }

    // run single-threaded multoplication
    SingleThreadedMultiplication(A, B, OUT, SIZE);
    for (size_t i = 0; i < SIZE; i++)
        for (size_t j = 0; j < SIZE; j++)
            OUT[i][j] = 0;

    // run single-threaded multoplication with dot product optimization
    SingleThreadedMultiplicationWithdotproduct(A, B, OUT, SIZE);
    for (size_t i = 0; i < SIZE; i++)
        for (size_t j = 0; j < SIZE; j++)
            OUT[i][j] = 0;

    // run single-threaded multoplication with dot product optimization and transposed B optimization
    SingleThreadedMultiplicationWithTransposeAndDot(A, B, OUT, SIZE);
    for (size_t i = 0; i < SIZE; i++)
        for (size_t j = 0; j < SIZE; j++)
            OUT[i][j] = 0;

    // run parallel multiplication
    ParallelMultiplication(A, B, OUT, SIZE);
    for (size_t i = 0; i < SIZE; i++)
        for (size_t j = 0; j < SIZE; j++)
            OUT[i][j] = 0;

    // run parallel multoplication with dot product optimization
    ParallelMultiplicationWithdotptoduct(A, B, OUT, SIZE);
    for (size_t i = 0; i < SIZE; i++)
        for (size_t j = 0; j < SIZE; j++)
            OUT[i][j] = 0;

    // run parallel multiplication with transposed B optimization
    ParallelMultiplicationWithtransposedB(A, B, OUT, SIZE);
    for (size_t i = 0; i < SIZE; i++)
        for (size_t j = 0; j < SIZE; j++)
            OUT[i][j] = 0;

    // run parallel multiplication with all possible optimizations
    ParallelMultiplicationMaxPerformance(A, B, OUT, SIZE);

    // clear all pointers
    for (size_t i = 0; i < SIZE; i++)
    {
        delete[] A[i];
        delete[] B[i];
        delete[] OUT[i];
    }
    delete[] A;
    delete[] B;
    delete[] OUT;

    return 0;
}