/*
    Second variant of task
    On the Figure_1 displayed solutions for b = 0.11
    On Figure_2 we can see that nothing odd is happening around b=1.5

    Here is the algorithm without reduction
*/

#include "solvers.h"

int main()
{
// считаем для b = 0..1
#pragma omp parallel for
    for (int i = 0; i <= 10; ++i)
    {
        diffur_solver solver(0.1 * i, POINTS);
        solver.solve();

        std::string filename = "file" + std::to_string(i) + ".dat";
        solver.print_to_file(filename);
    }

    return 0;
}