/**
 * LocalSearch.hpp
 * created on : Nov 30 2022
 * author : Z.LEI
 **/

#ifndef CETSP_LOCALSEARCH_HPP
#define CETSP_LOCALSEARCH_HPP

#include "Defs.hpp"
#include "Genetic/List.hpp"
#include "Utils/Parameters.hpp"
#include "Utils/Random.hpp"
#include "Geometry.hpp"
#include "Neighbor.hpp"
#include "LocalSearch/LKH.hpp"
#include "Solver.hpp"
#include "Greed.hpp"
#include <chrono>

class LocalSearch {
private:
    std::vector<double> costs;
    Random *random;
    Centers centers;
    Neighbors neighbors;
    Neighbor* neighbor;
    LKH lkh;
    Greed greed;
    Solver solver;
    std::string improvement;
    int lkh_random_num;
    void jointOpt(List* s);
    void randomTwoOpt(List* s);
    void bestImproveApproxRelocate(List* s);
    void bestImproveApproxSwap(List* s);
    void firstImproveApproxRelocate(List* s);
    void firstImproveApproxSwap(List* s);
public:
    LocalSearch(Parameters *params);
    ~LocalSearch();
    void setContext(Random *random, Centers &centers, Neighbor* neighbor, std::string timestamp);
    List *initSolOpt(List *s);
    List *VND(List *s);
};

#endif // CETSP_LOCALSEARCH_HPP