/**
 * GAX.hpp
 * created on : Jan 12 2023
 * author : Z.LEI
 **/

#ifndef CETSP_GAX_HPP
#define CETSP_GAX_HPP

#include "Crossover.hpp"

class GAX : public Crossover {
public:
    GAX();
    ~GAX();
    List* realRun(List* s1, List* s2);
};


#endif //CETSP_GAX_HPP
