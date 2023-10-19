/**
 * Distance.hpp
 * created on : Feb 20 2023
 * author : Z.LEI
 **/

#ifndef CETSP_DISTANCE_HPP
#define CETSP_DISTANCE_HPP

#include "Defs.hpp"
#include "List.hpp"
#include <iostream>

class Distance {
private:
    static double editDistance(List *s1, List *s2);
    static double JaroDistance(List *s1, List *s2);
    static double JaroEdgeDistance(List *s1, List *s2);
    static double moveDistance(List *s1, List *s2);
    static double moveEdgeDistance(List *s1, List *s2);
public:
    Distance();
    ~Distance();
    static double run(List *s1, List *s2);
};


#endif //CETSP_DISTANCE_HPP
