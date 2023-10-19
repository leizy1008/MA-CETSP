/**
 * CrossoverFactory.hpp
 * created on : March 07 2023
 * author : Z.LEI
 **/

#ifndef CETSP_CROSSOVERFACTORY_HPP
#define CETSP_CROSSOVERFACTORY_HPP

#include "Defs.hpp"
#include "Crossover.hpp"
#include "EAX.hpp"
#include "KSX.hpp"
#include "GAX.hpp"

class CrossoverFactory {
public:
    CrossoverFactory();
    ~CrossoverFactory();
    static Crossover* createCrossover(std::string crossover_type);
};

#endif //CETSP_CROSSOVERFACTORY_HPP
