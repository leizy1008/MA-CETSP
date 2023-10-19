/**
 * Distance.cpp
 * created on : Feb 20 2023
 * author : Z.LEI
 **/

#include "Genetic/Distance.hpp"

Distance::Distance() {}
Distance::~Distance() {}

double Distance::run(List *s1, List *s2) {
    if (DISTANCE == "EDIT") {
        return editDistance(s1, s2);
    } else if (DISTANCE == "JARO_EDGE") {
        return JaroEdgeDistance(s1, s2);
    } else if (DISTANCE == "MOVE_EDGE") {
        return moveEdgeDistance(s1, s2);
    } else {
        std::cout << "[Error] distance function" << std::endl;
        return 0;
    }
}

double Distance::JaroEdgeDistance(List *s1, List *s2) {
    int size = s1->size();
    std::vector<std::vector<int>> indices(size, std::vector<int> {0, 0});
    Node *p1 = s1->head(), *p2 = s2->head();
    for (int i = 0; i < size; ++i) {
        indices[p1->id][0] = i;
        indices[p2->id][1] = i;
        p1 = p1->next;
        p2 = p2->next;
    }

    double match = 0, t1 = 0, t2 = 0;
    double threshold = int(size / 10) >= 10 ? 10 : int(size / 10);

    p1 = s1->head();
    for (int i = 0; i < size; ++i) {
        int vi = p1->id, vj = p1->next->id;
        int diff = abs(indices[vi][1] - indices[vj][1]);
        diff = diff <= int(size / 2) ? diff : size - diff;
        if (diff == 1) ++match;
        else if (diff <= threshold) ++t1;
        p1 = p1->next;
    }

    p2 = s2->head();
    for (int i = 0; i < size; ++i) {
        int vi = p2->id, vj = p2->next->id;
        int diff = abs(indices[vi][0] - indices[vj][0]);
        diff = diff <= int(size / 2) ? diff : size - diff;
        if (diff > 1 && diff <= threshold) ++t2;
        p2 = p2->next;
    }

    if (match + t1 + t2 == 0) return 100;
    double similarity =  ((2 * match + t1 + t2) / (2 * size) + (2 * match) / (2 * match + t1 + t2)) / 2;
    return 100 * (1 - similarity);
}

double Distance::moveEdgeDistance(List *s1, List *s2) {
    int size = s1->size();
    std::vector<std::vector<int>> indices(size, std::vector<int> {0, 0});
    Node *p1 = s1->head(), *p2 = s2->head();
    for (int i = 0; i < size; ++i) {
        indices[p1->id][0] = i;
        indices[p2->id][1] = i;
        p1 = p1->next;
        p2 = p2->next;
    }

    int match = 0, move1 = 0, move2 = 0;
    p1 = s1->head();
    for (int i = 0; i < size; ++i) {
        int vi = p1->id, vj = p1->next->id;
        int diff = abs(indices[vi][1] - indices[vj][1]);
        diff = diff <= int(size / 2) ? diff : size - diff;
        if (diff == 1) ++match;
        else move1 += (diff - 1);
        p1 = p1->next;
    }

    p2 = s2->head();
    for (int i = 0; i < size; ++i) {
        int vi = p2->id, vj = p2->next->id;
        int diff = abs(indices[vi][0] - indices[vj][0]);
        diff = diff <= int(size / 2) ? diff : size - diff;
        if (diff > 1) move2 += (diff - 1);
        p2 = p2->next;
    }

    return (move1 + move2) / 2;
}

double Distance::JaroDistance(List *s1, List *s2) {
    int size = s1->size();
    std::vector<std::vector<int>> indices(size, std::vector<int> {0, 0});
    Node *p1 = s1->head(), *p2 = s2->head();
    for (int i = 0; i < size; ++i) {
        if (i <= size / 2) {
            indices[p1->id][0] = i;
            indices[p2->id][1] = i;
        } else {
            indices[p1->id][0] = size - i;
            indices[p2->id][1] = size - i;
        }
        p1 = p1->next;
        p2 = p2->next;
    }

    double threshold = int(size / 10) - 1;
    double m = 0, t = 0;
    for (int i = 0; i < indices.size(); ++i) {
        int diff = abs(indices[i][0] - indices[i][1]);
        if (diff == 0) ++m;
        else if (diff <= threshold) ++t;
    }

    double similarity =  (2 * (m + t) / size + m / (m + t)) / 3;
    return 100 * (1 - similarity);

}

double Distance::moveDistance(List *s1, List *s2) {
    int size = s1->size();
    std::vector<std::vector<int>> indices(size, std::vector<int> {0, 0});
    Node *p1 = s1->head(), *p2 = s2->head();
    for (int i = 0; i < size; ++i) {
        if (i <= size / 2) {
            indices[p1->id][0] = i;
            indices[p2->id][1] = i;
        } else {
            indices[p1->id][0] = size - i;
            indices[p2->id][1] = size - i;
        }
        p1 = p1->next;
        p2 = p2->next;
    }
    int sum = 0;
    for (int i = 0; i < indices.size(); ++i) {
        sum += abs(indices[i][0] - indices[i][1]);
    }
    return sum;
}

double Distance::editDistance(List *s1, List *s2) {
    // edit distance
    int size = s1->size();
    // lower triangular storage, i > j, for edit distance
    std::vector<int> edges(size * (size - 1) / 2, 0);

    Node *p1 = s1->head();
    Node *p2 = s2->head();
    double dist = 2 * size;
    for (int i = 0; i < size; ++i) {
        int id1, id2, ind1, ind2, index;
        // edges in s1
        id1 = p1->id;
        id2 = p1->next->id;
        ind1 = id1 > id2 ? id1 : id2;
        ind2 = id1 > id2 ? id2 : id1;
        index = ind1 * (ind1 - 1) / 2 + ind2;
        if (edges[index] == 0) {
            edges[index] = 1;
        } else if (edges[index] = 1) {
            // common edge
            dist -= 2;
        }
        // edges in s2
        id1 = p2->id;
        id2 = p2->next->id;
        ind1 = id1 > id2 ? id1 : id2;
        ind2 = id1 > id2 ? id2 : id1;
        index = ind1 * (ind1 - 1) / 2 + ind2;
        if (edges[index] == 0) {
            edges[index] = 1;
        } else if (edges[index] = 1) {
            // common edge
            dist -= 2;
        }
        // next
        p1 = p1->next;
        p2 = p2->next;
    }

    return 100 * dist / (2 * size);
}
