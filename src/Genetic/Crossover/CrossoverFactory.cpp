/**
 * CrossoverFactory.cpp
 * created on : March 07 2023
 * author : Z.LEI
 **/

#include "Genetic/Crossover/CrossoverFactory.hpp"

CrossoverFactory::CrossoverFactory() {}
CrossoverFactory::~CrossoverFactory() {}

Crossover *CrossoverFactory::createCrossover(std::string crossover_type) {
    if (crossover_type == "GAX") {
        return new GAX();
    } else if (crossover_type == "KSX") {
        return new KSX();
    } else if (crossover_type == "EAX") {
        return new EAX();
    } else {
        std::cerr << "[ERROR] crossover function" << std::endl;
    }
    return nullptr;
}