/**
 * KSX.cpp
 * created on : Feb 17 2023
 * author : Z.LEI
 **/

#include "Genetic/Crossover/KSX.hpp"

KSX::KSX() {}
KSX::~KSX() {}

List *KSX::realRun(List *s1, List *s2) {
    int size = s1->size();
    this->k_step = random->randomInt(size / 2) + 1;

    A_link.clear();
    B_link.clear();
    positions.clear();
    visited.clear();
    A_link.resize(size, std::vector<int> (2, -1));
    B_link.resize(size, std::vector<int> (2, -1));
    positions.resize(size, std::vector<double> {-1, -1, -1, -1});
    visited.resize(size, false);

    Node *pa = s1->head();
    Node *pb = s2->head();
    for (int i = 0; i < size; ++i) {
        A_link[pa->id][0] = pa->pre->id;
        A_link[pa->id][1] = pa->next->id;

        B_link[pb->id][0] = pb->pre->id;
        B_link[pb->id][1] = pb->next->id;

        positions[pa->id][0] = pa->x;
        positions[pa->id][1] = pa->y;
        positions[pb->id][2] = pb->x;
        positions[pb->id][3] = pb->y;

        pa = pa->next;
        pb = pb->next;
    }

    // construct the cycle
    std::vector<std::vector<int>> completed_cycle;
    while (true) {
        if (completed_cycle.size() == size) break;    // tour has been completed

        bool which_parent;
        int next;
        int insert_index;
        if (completed_cycle.size() > 0) {
            int lucky = random->randomInt(completed_cycle.size());
            int i;
            for (i = 0; i < completed_cycle.size(); ++i) {
                insert_index = (lucky + i) % completed_cycle.size() + 1;
                next = completed_cycle[insert_index-1][1];
                if (A_link[next][0] != -1 || A_link[next][1] != -1) {
                    which_parent = false;
                    break;
                } else if (B_link[next][0] != -1 || B_link[next][1] != -1) {
                    which_parent = true;
                    break;
                }
            }
            if (i == completed_cycle.size()) break;
        } else {
            which_parent = random->randomInt(2) == 0 ? true : false;
            next = random->randomInt(size);
            insert_index = 0;
        }

        std::vector<std::vector<int>> cycle;
        if (!visited[next]){
            cycle.emplace_back(std::vector<int> {which_parent, next});
            visited[next] = true;
        }

        bool warning = false;
        int step = 0;

        while (true) {
            int pre = next;
            auto &link = which_parent ? A_link : B_link;
            int edge1 = link[next][0];
            int edge2 = link[next][1];
            if (edge1 == -1 && edge2 == -1) {
                if (warning) break;                 // both parents have no available edges, the cycle is completed
                which_parent = ! which_parent;      // switch to the other parent
                warning = true;
                if (step == 0) step = k_step;       // if no step has been take in this parent, only borrow one edge from the other parent
                else step = 0;                      // if some steps have been taken in this parent, then switch to the other parent for all steps
                continue;
            }
            if (warning) {
                warning = false;
            }
            if (edge1 == -1) {
                link[next][1] = -1;
                next = edge2;
            } else if (edge2 == -1) {
                link[next][0] = -1;
                next = edge1;
            } else {
                if (random->randomInt(2) == 0) {
                    link[next][0] = -1;
                    next = edge1;
                } else {
                    link[next][1] = -1;
                    next = edge2;
                }
            }
            if (link[next][0] == pre) link[next][0] = -1;
            if (link[next][1] == pre) link[next][1] = -1;

            if (!visited[next]){
                cycle.emplace_back(std::vector<int> {which_parent, next});
                visited[next] = true;
            }

            if (++step >= k_step) {
                which_parent = !which_parent;
                step = 0;
            }
        }
        completed_cycle.insert(completed_cycle.begin() + insert_index, cycle.begin(), cycle.end());
    }

    // construct the solution
    List* s = new List();
    Node* real_head = nullptr;
    for (int i = 0; i < completed_cycle.size(); ++i) {
        int p = completed_cycle[i][0];
        int id = completed_cycle[i][1];
        Node* node = new Node(id, positions[id][2*p], positions[id][2*p+1]);
        if (id == 0) real_head = node;
        s->add(node);
    }
    s->setHead(real_head);
    return s;
}
