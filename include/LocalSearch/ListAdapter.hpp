/**
 * ListAdapter.hpp
 * created on : Jan 03 2023
 * author : Z.LEI
 **/

#ifndef CETSP_LISTADAPTER_HPP
#define CETSP_LISTADAPTER_HPP

#include "Genetic/Node.hpp"
#include "Genetic/List.hpp"
#include <vector>

class ListAdapter {
private:
    std::vector<std::vector<int>> nodes;
    std::vector<std::vector<double>> positions;
public:
    ListAdapter();
    ~ListAdapter();
    List* real2Reduced(List* real_list);        // real list to reduced list
    List* reduced2Real(List* reduced_list);     // reduced list to real list
};

#endif //CETSP_LISTADAPTER_HPP
