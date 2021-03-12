#include <stdio.h>
#include <omp.h>
#include <vector>
#include <string>
#include <iostream>
#include <chrono>

constexpr std::size_t N = 1 << 25;
using std::chrono::duration_cast;
using std::chrono::high_resolution_clock;
using std::chrono::milliseconds;

#define SCHEDULE dynamic
#define NAME blur_dynamic
#include "calcFun.h"

#define SCHEDULE static
#define NAME blur_static
#include "calcFun.h"

#define SCHEDULE auto
#define NAME blur_auto
#include "calcFun.h"

template <class Fn>
long measure(Fn f)
{
    auto start = high_resolution_clock::now();
    f();
    auto end = high_resolution_clock::now();
    auto elapsed = duration_cast<milliseconds>(end - start);
    return elapsed.count();
}

std::vector<int> initSequenceVector(int N)
{
    std::vector<int> vect;
    vect.reserve(N);
    for (std::size_t i = 0; i < N; i++)
        vect.push_back(i);
    return vect;
}

int main(int argc, char **argv)
{
    auto vect = initSequenceVector(N);
    // auto elapsed = measure([&vect]() { calculate(vect); });

    auto dtime = measure([&vect]() { blur_dynamic(vect); });
    std::cout << "Dynamic: " << dtime << "ms\n";

    auto atime = measure([&vect]() { blur_auto(vect); });
    std::cout << "Auto: " << atime << "ms\n";

    auto stime = measure([&vect]() { blur_static(vect); });
    std::cout << "Static: " << stime << "ms\n";
    // std::cout << "Past: " << elapsed << "ms";
    return 0;
}