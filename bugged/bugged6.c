/******************************************************************************
 * ЗАДАНИЕ: bugged6.c
 * ОПИСАНИЕ:
 *   Множественные ошибки компиляции
 *   Программа должнна была показывать, как можно выполнять параллельный код,
 *   используя функции, но что-то пошло не так.
 ******************************************************************************/

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define VECLEN 100

float a[VECLEN], b[VECLEN];
float sum = 0.0;

void dotprod()
{
    int i, tid;

    tid = omp_get_thread_num();
#pragma omp for reduction(+ \
                          : sum)
    for (i = 0; i < VECLEN; i++)
    {
        sum = sum + (a[i] * b[i]);
        printf("  tid= %d i=%d\n", tid, i);
    }
}

int main(int argc, char *argv[])
{
    int i;

    for (i = 0; i < VECLEN; i++)
        a[i] = b[i] = 1.0 * i;

#pragma omp parallel shared(sum)
    dotprod();

    printf("Sum = %f\n", sum);
}
