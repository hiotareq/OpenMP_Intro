#pragma once

#include <vector>

struct matrix
{
    matrix()
    {
        n_ = 0;
    }

    matrix(int n)
    {
        n_ = n;
        a_.resize(n_);
        for (int i = 0; i < n_; ++i)
        {
            a_[i].resize(n_);
        }
    }

    ~matrix()
    {
    }

    std::vector<std::vector<double>> a_;
    int n_ = 0;
};