/**
 * Neighbor.cpp
 * created on : Jan 31 2023
 * author : Z.LEI
 **/

#include "LocalSearch/Neighbor.hpp"

Neighbor::Neighbor(int neighbor_size) {
    max_neighbor_size = NEIGHBOR_SIZE;
}
Neighbor::~Neighbor() {}

void Neighbor::setContext(int size) {
    count = 0;
    neighbor_size = size > max_neighbor_size ? max_neighbor_size : size;
    centroids.resize(size, std::vector<double> {0, 0});
    distances.resize(size, std::vector<double> (size, 0));
    neighbors.resize(size, std::vector<int> (size, 0));
}

void Neighbor::updateCentroids(List *s) {
    Node* p = s->head();
    for (int i = 0; i < s->size(); ++i) {
        centroids[p->id][0] = (count * centroids[p->id][0] + p->x) / (count + 1);
        centroids[p->id][1] = (count * centroids[p->id][1] + p->y) / (count + 1);
        p = p->next;
    }
    ++count;
}

void Neighbor::updateNeighbors() {
    int size = centroids.size();
    for (int i = 0; i < size; ++i) {
        for (int j = i + 1; j < size; ++j) {
            double dist = Geometry::EucDistance(centroids[i][0], centroids[i][1], centroids[j][0], centroids[j][1]);
            distances[i][j] = dist;
            distances[j][i] = dist;
        }
    }
    neighbors.resize(size, std::vector<int> (size, 0));
    for (int i = 0; i < size; ++i) {
        std::vector<double> distance = distances[i];
        std::sort(distance.begin(), distance.end());
        double threshold = distance[neighbor_size-1];
        for (int j = 0; j < size; ++j) {
            if (distances[i][j] > 0 && distances[i][j] <= threshold) {
                neighbors[i][j] = 1;
                neighbors[j][i] = 1;
            }
        }
    }
}

std::vector<std::vector<int>> Neighbor::getNeighbors() {
    return neighbors;
}

std::vector<std::vector<double>> Neighbor::getCentroids() {
    return centroids;
}