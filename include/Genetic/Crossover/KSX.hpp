/**
 * KSX.hpp
 * created on : Feb 17 2023
 * author : Z.LEI
 **/

#ifndef CETSP_KSX_HPP
#define CETSP_KSX_HPP

#include "Utils/Random.hpp"
#include "List.hpp"
#include "LocalSearch/Neighbor.hpp"
#include "Crossover.hpp"

class KSX : public Crossover {
private:
    std::vector<std::vector<int>> A_link;
    std::vector<std::vector<int>> B_link;
    std::vector<std::vector<double>> positions;
    std::vector<bool> visited;
    int k_step;
public:
    KSX();
    ~KSX();
    List* realRun(List* s1, List* s2);
};

#endif //CETSP_KSX_HPP
