/**
 * Random.cpp
 * created on : Nov 30 2022
 * author : Z.LEI
 **/

#include "Utils/Random.hpp"

Random::Random(int init_seed) {
    std::random_device rand_dev;
    int seed = init_seed == 0 ? rand_dev() : init_seed;
    if (LOG) std::cout << "seed: " << seed << std::endl;
    srand(seed);
    generator.seed(seed);
}

Random::~Random() {}

int Random::randomInt(int n) {
    return rand() % n;
}

double Random::randomDoubleDistr(double a, double b) {
    std::uniform_real_distribution<double> distr(a, b);
    return distr(generator);
}


