#pragma once
#include <vector>

class vector // geometrical vector
{
public:
    vector() = delete;

    vector(int n)
    {
        n_ = n;
        v_.resize(n_);
    }

    ~vector()
    {
    }

    const double &operator[](size_t i) const
    {
        return v_[i];
    }

    double &operator[](size_t i)
    {
        return v_[i];
    }

    vector operator-(const vector &rhs)
    {
        assert(rhs.n_ == n_);
        vector result{n_};
        for (int i = 0; i < n_; ++i)
        {
            result[i] = v_[i] - rhs[i];
        }
        return result;
    }

    vector &operator=(const vector &rhs)
    {
        if (&rhs == this)
        {
            return *this;
        }

        n_ = rhs.n_;
        v_.resize(n_);
        for (int i = 0; i < n_; ++i)
        {
            v_[i] = rhs[i];
        }

        return *this;
    }

    int size() const
    {
        return n_;
    }

private:
    std::vector<double> v_;
    int n_;
};