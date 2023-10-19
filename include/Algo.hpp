/**
 * Algo.hpp
 * created on : Nov 30 2022
 * author : Z.LEI
 **/

#ifndef CETSP_ALGO_HPP
#define CETSP_ALGO_HPP

#include "Defs.hpp"
#include "Utils/Parameters.hpp"
#include "Utils/Data.hpp"
#include "List.hpp"
#include "Genetic/Population.hpp"
#include <vector>
#include <chrono>
#include <climits>

class Algo {
private:
    Random *random;
    Parameters *params;
    Data data;
    Population population;
    int iteration;
    int patience_threshold;
    int instance_index;
    std::string timestamp;  // timestamp
public:
    Algo(Parameters *params);
    ~Algo();
    void run();
};

#endif //CETSP_ALGO_HPP
