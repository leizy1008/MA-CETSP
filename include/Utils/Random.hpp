/**
 * Random.hpp
 * created on : Nov 30 2022
 * author : Z.LEI
 **/

#ifndef CETSP_RANDOM_HPP
#define CETSP_RANDOM_HPP

#include "Defs.hpp"
#include <iostream>
#include <random>
#include <algorithm>

class Random {
private:
    std::mt19937 generator;
public:
    Random(int init_seed);
    ~Random();
    int randomInt(int n);                                   // get random int
    double randomDoubleDistr(double a, double b);           // get random double in distribution
    template <typename T>                                   // get a permutation
    void permutation(std::vector<T> &vec) {
        std::shuffle(vec.begin(), vec.end(), generator);
    }
};

#endif //CETSP_RANDOM_HPP
