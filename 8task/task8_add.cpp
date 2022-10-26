#include <iostream>
#include <omp.h>
#include <vector>
#include <fstream>
#include <string.h>
#include <typeinfo>

// Hoare breakdown, basically taken from Wikipedia
size_t partition(std::vector<int32_t> &arr, size_t low, size_t high)
{
    size_t pivot = (arr[low] + arr[high]) >> 1;
    size_t i = low;
    size_t j = high;

    while (true)
    {
        while (arr[i] < pivot)
            ++i;
        while (arr[j] > pivot)
            --j;
        if (i >= j)
            return j;
        std::swap(arr[i++], arr[j--]);
    }
}

void quicksort(std::vector<int32_t> &arr, size_t low, size_t high)
{
    if (low >= high)
        return;
    // this critical section is only for beautiful output, we don't need it otherwise and it worsen performane of sorting in general
    /*
    #pragma omp critical
        {
            std::cout << "Thread number " << omp_get_thread_num() << " low = " << low << " high = " << high << "\n";
        }
    */

    // detect Pivot element with Hoare breakdown
    size_t p = partition(arr, low, high);
    // for now pivot element is arr[p]

// give tasks to child threads
#pragma omp task firstprivate(arr, low, p)
    {
        quicksort(arr, low, p);
    }
#pragma omp task firstprivate(arr, low, p)
    {
        quicksort(arr, p + 1, high);
    }
}

int main(int argc, char *argv[])
{
    // vector to sort
    std::vector<int32_t> arr(std::atoi(argv[1]));

    // booleans to announce border cases
    bool borderOrder = true, borderReverse = true;

    // variable for checking border cases
    int32_t last = INT32_MIN;

    // input from keyboard or file
    if (argc == 3)
    {
        // input from keyboard
        if (strcmp("k", argv[2]) == 0)
        {
            for (auto &num : arr)
            {
                std::cin >> num;
                // checking border case where array is an ascending order
                if (num < last)
                    borderOrder = false;
                // checking border case where array is an descending order
                if (num > last)
                    borderReverse = false;
                last = num;
            }
            // if reversed order reverse array
            if (borderReverse)
                for (size_t i = 0; i < arr.size() / 2; ++i)
                    std::swap(arr[i], arr[arr.size() - 1 - i]);
            // if border case, return
            if (borderOrder || borderReverse)
            {
                std::cout << "Returned by border case\n";
                return 1;
            }
        }
        else
        {
            std::cout << "Wrong flag\n";
            return -1;
        }
    }
    else if (argc == 4)
    {
        // imput from file
        if (strcmp(argv[2], "f") == 0)
        {
            std::ifstream f;
            f.open(argv[3]);
            if (!f.is_open())
            {
                std::cerr << "Couldn't open file\n";
                return -1;
            }
            else
            {
                for (auto &num : arr)
                {
                    f >> num;
                    // checking border case where array is an ascending order
                    if (num < last)
                        borderOrder = false;
                    // checking border case where array is an descending order
                    if (num > last)
                        borderReverse = false;
                    last = num;
                }
                // if reversed order reverse array
                if (borderReverse)
                    for (size_t i = 0; i < arr.size() / 2; ++i)
                        std::swap(arr[i], arr[arr.size() - 1 - i]);
                // if border case, return
                if (borderOrder || borderReverse)
                {
                    std::cout << "Returned by border case\n";
                    return 1;
                }
            }
        }
        else
        {
            std::cout << "Wrong flag\n";
            return -1;
        }
    }
    // Random input
    if (argc == 2)
        for (auto &num : arr)
            num = rand() % arr.size() + 1;

#pragma omp parallel
    {
#pragma omp single nowait
        quicksort(arr, 0, arr.size() - 1);
    }
    // commented code to looak if resulting array is sorted
    /*  for(auto& num : arr)
            std::cout << num << " ";
        std::cout << "\n";
    */

    return 0;
}