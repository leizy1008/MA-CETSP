/**
 * Parameters.hpp
 * created on : Nov 30 2022
 * author : Z.LEI
 **/

#ifndef CETSP_PARAMETERS_HPP
#define CETSP_PARAMETERS_HPP


#include <iostream>
#include <random>
#include <ctime>
#include "cmdline.h"
#include "Defs.hpp"

class Parameters {
public:
    int seed = 0;
    int random_num;
    std::string timestamp;
    std::string init;
    std::string select;
    std::string crossover;
    std::string improvement;
    std::string greed;
    std::string distance;
    int instance_index;
    int population_size;
    int iteration;
    int patience;
    double max_time;
    double fit_beta;
    int dist_th;
    int neighbor_size;
    Parameters(int argc, char **argv);
    Parameters() = default;
    ~Parameters() = default;
    void print() const;
};


#endif //CETSP_PARAMETERS_HPP
