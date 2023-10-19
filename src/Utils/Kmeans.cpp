/**
 * Kmeans.cpp
 * created on : Feb 08 2023
 * author : Z.LEI
 **/

#include "Utils/Kmeans.hpp"

Kmeans::Kmeans() {}
Kmeans::~Kmeans() {}

void Kmeans::setContext(Random *random, Centers &centers) {
    this->k = sqrt(centers.size()) + 0.5;
    this->max_iter = 100;
    this->random = random;
    this->centers = centers;
    this->centroids.resize(k, std::vector<double> {});
    this->groups.resize(k, std::vector<int> {});
}

int Kmeans::closest(std::vector<double> &p) {
    int index = 0;
    double min_dist = Geometry::EucDistance(p[0], p[1], centroids[0][0], centroids[0][1]);
    for (int i = 1; i < k; ++i) {
        double curr_dist = Geometry::EucDistance(p[0], p[1], centroids[i][0], centroids[i][1]);
        if (curr_dist < min_dist) {
            index = i;
            min_dist = curr_dist;
        }
    }
    return index;
}

void Kmeans::run() {
    // Initialize centers randomly
    for (int i = 0; i < k; ++i) {
        int random_index = random->randomInt(centers.size());
        centroids[i] = centers[random_index];
    }

    for (int iter = 0; iter < max_iter; ++iter) {
        std::vector<int> count(k, 0);
        std::vector<std::vector<double>> sum(k, std::vector<double> (2, 0));

        // Assign points to the closest center
        for (int i = 0; i < centers.size(); ++i) {
            int index = closest(centers[i]);
            if (iter == max_iter - 1) {
                groups[index].emplace_back(i);
            }
            count[index]++;
            for (int j = 0; j < 2; ++j) {
                sum[index][j] += centers[i][j];
            }
        }

        // Update centers
        for (int i = 0; i < k; ++i) {
            for (int j = 0; j < 2; ++j) {
                centroids[i][j] = sum[i][j] / count[i];
            }
        }
    }
}

std::vector<std::vector<int>> Kmeans::getGroups() {
    return groups;
}