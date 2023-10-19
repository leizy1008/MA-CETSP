/**
 * Crossover.cpp
 * created on : Jan 12 2023
 * author : Z.LEI
 **/

#include "Genetic/Crossover/Crossover.hpp"

Crossover::Crossover() {}
Crossover::~Crossover() {}

void Crossover::setContext(Random *random) {
    this->random = random;
}

List* Crossover::run(List *s1, List *s2) {
    auto start = std::chrono::high_resolution_clock::now();
    List *s = realRun(s1, s2);
    auto end = std::chrono::high_resolution_clock::now();
    if (LOG) {
        std::cout << "parents values: " << s1->getValue() << " " << s2->getValue() << std::endl;
        std::cout << CROSSOVER << " time : " << std::chrono::duration<double> (end - start).count() << " s" << std::endl;
    }
    return s;
}
