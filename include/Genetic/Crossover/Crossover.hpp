/**
 * Crossover.hpp
 * created on : Jan 12 2023
 * author : Z.LEI
 **/

#ifndef CETSP_CROSSOVER_HPP
#define CETSP_CROSSOVER_HPP

#include "Genetic/List.hpp"
#include "Utils/Random.hpp"
#include "LocalSearch/Neighbor.hpp"
#include <chrono>

class Crossover {
protected:
    Random *random;
public:
    Crossover();
    ~Crossover();
    void setContext(Random *random);
    List* run(List* s1, List* s2);
    virtual List* realRun(List* s1, List* s2) = 0;
};

#endif //CETSP_CROSSOVER_HPP
