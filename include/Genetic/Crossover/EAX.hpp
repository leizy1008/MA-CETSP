/**
 * EAX.hpp
 * created on : Jan 12 2023
 * author : Z.LEI
 **/

#ifndef CETSP_EAX_HPP
#define CETSP_EAX_HPP

#include "Crossover.hpp"
#include <unordered_map>

class EAX : public Crossover{
private:
    int eax_threshold;
    int strategy; // 1 : simple; 2 : block
    int count;
    std::vector<std::vector<int>> A_link;
    std::vector<std::vector<int>> B_link;
    std::vector<std::vector<int>> intermediate;
    std::vector<std::vector<int>> AB_cycles;
    std::vector<std::vector<int>> E_sets;
    std::vector<std::vector<double>> positions;
    Neighbor* neighbor;
    void adjList(List* s1, List* s2);               // construct linked table
    void deleteCommonEdge();
    void ABCycles();
    void ESets();                                   // simple : choose randomly one AB-cycle as E-set, block : an additional cycle
    void intermediateSol();                         // construct intermediate solution
    List* completeSol();                            // construction feasible solution
    void connectTours(List* s1, List* s2);          // connect all tours to form only one tour
public:
    EAX();
    ~EAX();
    List* realRun(List* sa, List* sb);
};


#endif //CETSP_EAX_HPP
