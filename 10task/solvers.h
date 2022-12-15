#pragma once

#include <iostream>
#include <cmath>
#include <cassert>
#include <string>
#include <fstream>
#include <vector>

#include "matrix.h"
#include "vector.h"

#include <omp.h>

// для редукции необходимо число точек 2^n + 1, но пока использую 2000 для трехдиагональной прогонки
constexpr int POINTS = 2000;
constexpr double STEP = 0.0005;

class diffur_solver
{
public:
    diffur_solver(const double b, const int N)
    {
        b_ = b;
        N_ = N;
        solution_.resize(N_);
    }

    ~diffur_solver()
    {
    }

    void solve();
    void print_to_file(const std::string &filename);

private:
    double b_ = 0;
    int N_ = 0;
    std::vector<double> solution_;
};

class sole_solver
{
public:
    sole_solver(const matrix &A, const vector &y) : A_(A), y_(y) {}
    vector progonka_solve();
    vector reduction_solve();

private:
    const matrix &A_;
    const vector &y_;
};