/**
 * Kmeans.hpp
 * created on : Feb 08 2023
 * author : Z.LEI
 **/

#ifndef CETSP_KMEANS_HPP
#define CETSP_KMEANS_HPP

#include "Utils/Geometry.hpp"
#include "Utils/Random.hpp"

class Kmeans {
private:
    Random *random;
    Centers centers;
    std::vector<std::vector<double>> centroids;
    std::vector<std::vector<int>> groups;
    int k;
    int max_iter;
    int closest(std::vector<double> &p);
public:
    Kmeans();
    ~Kmeans();
    void setContext(Random *random, Centers &centers);
    void run();
    std::vector<std::vector<int>> getGroups();
};


#endif //CETSP_KMEANS_HPP
