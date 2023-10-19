/**
 * Neighbor.hpp
 * created on : Jan 31 2023
 * author : Z.LEI
 **/

#ifndef CETSP_NEIGHBOR_HPP
#define CETSP_NEIGHBOR_HPP

#include "Genetic/List.hpp"
#include "Geometry.hpp"
#include <vector>

class Neighbor {
private:
    int count;
    int max_neighbor_size;
    int neighbor_size;
    std::vector<std::vector<double>> centroids;     // centroids of historical positions
    std::vector<std::vector<double>> distances;     // distances between centroids
    Neighbors neighbors;                            // neighbors
public:
    Neighbor(int neighbor_size);
    ~Neighbor();
    void setContext(int size);
    void updateCentroids(List* s);
    void updateNeighbors();
    std::vector<std::vector<double>> getCentroids();
    Neighbors getNeighbors();
};


#endif //CETSP_NEIGHBOR_HPP
