/**
 * EAX.cpp
 * created on : Jan 12 2023
 * author : Z.LEI
 **/

#include "Genetic/Crossover/EAX.hpp"

EAX::EAX() {
    strategy = 1;
    eax_threshold = 500;
    count = 0;
}

List *EAX::realRun(List *s1, List *s2) {
    if (count == eax_threshold) strategy = 2;
    int size = s1->size();

    AB_cycles.clear();
    E_sets.clear();
    A_link.clear();
    B_link.clear();
    positions.clear();
    A_link.resize(size, std::vector<int> (2, -1));
    B_link.resize(size, std::vector<int> (2, -1));
    positions.resize(size, std::vector<double> (2, -1));

    adjList(s1, s2);
    // deleteCommonEdge();
    ABCycles();
    ESets();
    // std::cout << "E_sets size : "<< E_sets.size() << std::endl;
    intermediateSol();
    return completeSol();
}

void EAX::adjList(List *s1, List *s2) {
    int size = positions.size();

    Node *pa = s1->head();
    Node *pb = s2->head();
    for (int i = 0; i < size; ++i) {
        A_link[pa->id][0] = pa->pre->id;
        A_link[pa->id][1] = pa->next->id;

        B_link[pb->id][0] = pb->pre->id;
        B_link[pb->id][1] = pb->next->id;

        // positions[pa->id][0] = pa->x;
        // positions[pa->id][1] = pa->y;

        if (positions[pa->id][0] == -1 || rand() % 2 == 0) {
            // if the position not visited or if it has been visited it has 50% chance
            positions[pa->id][0] = pa->x;
            positions[pa->id][1] = pa->y;
        }
        if (positions[pb->id][0] == -1 || rand() % 2 == 0) {
            positions[pb->id][0] = pb->x;
            positions[pb->id][1] = pb->y;
        }

        pa = pa->next;
        pb = pb->next;
    }
    intermediate = A_link;
}

void EAX::deleteCommonEdge() {
    int size = positions.size();
    for (int i = 0; i < size; ++i) {
        if (A_link[i][0] == B_link[i][0]) {
            A_link[i][0] = -1;
            B_link[i][0] = -1;
        } else if (A_link[i][0] == B_link[i][1]) {
            A_link[i][0] = -1;
            B_link[i][1] = -1;
        }
        if (A_link[i][1] == B_link[i][0]) {
            A_link[i][1] = -1;
            B_link[i][0] = -1;
        } else if (A_link[i][1] == B_link[i][1]) {
            A_link[i][1] = -1;
            B_link[i][1] = -1;
        }
    }
}

void EAX::ABCycles() {
    int size = positions.size();
    while (true) {
        int start = random->randomInt(size);
        int i;
        for (i = 0; i < size; ++i) {
            if (A_link[start][0] == -1 && A_link[start][1] == -1) start = (start + 1) % size;
            else break;
        }
        if (i == size) break;

        std::vector<int> cycle = {start};

        int next = start;
        bool which_parent = true;
        while (true) {
            int pre = next;
            auto& link = which_parent ? A_link : B_link;
            int edge1 = link[next][0];
            int edge2 = link[next][1];
            if (edge1 == -1 && edge2 == -1) {
                std::cout << "ERROR : both edges are -1" << std::endl;
                break;
            }
            if (edge1 == -1) {
                link[next][1] = -1;
                next = edge2;
            } else if (edge2 == -1) {
                link[next][0] = -1;
                next = edge1;
            } else {
                if (edge1 == start && cycle.size() % 2 == 1) {
                    link[next][1] = -1;
                    next = edge2;
                } else if (edge2 == start && cycle.size() % 2 == 1) {
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
            }
            if (link[next][0] == pre) link[next][0] = -1;
            if (link[next][1] == pre) link[next][1] = -1;
            cycle.emplace_back(next);

            if (next == start && cycle.size() % 2 != 0) break;

            which_parent = !which_parent;
        }
        if (cycle.size() != 3) AB_cycles.emplace_back(cycle);
    }
}

void EAX::ESets() {
    int lucky = random->randomInt(AB_cycles.size());
    E_sets.emplace_back(AB_cycles[lucky]);
    AB_cycles.erase(AB_cycles.begin() + lucky);

    if (strategy == 2) {
        std::unordered_map<int, bool> map;
        for (int i = 0; i < E_sets[0].size(); ++i) {
            map[E_sets[0][i]] = true;
        }
        random->permutation(AB_cycles);
        for (auto& cycle : AB_cycles) {
            for (int i = 0; i < cycle.size(); ++i) {
                if (map[cycle[i]]) {
                    E_sets.emplace_back(cycle);
                    return;
                }
            }
        }
    }
}

void EAX::intermediateSol() {
    for (auto& E_set : E_sets) {
        for (int i = 0; i < E_set.size() - 1; i = i + 2) {
            // delete A edges
            int in = E_set[i];
            int out = E_set[i+1];
            if (intermediate[in][0] == out) intermediate[in][0] = -1;
            else if (intermediate[in][1] == out) intermediate[in][1] = -1;
            if (intermediate[out][0] == in) intermediate[out][0] = -1;
            else if (intermediate[out][1] == in) intermediate[out][1] = -1;
        }
        for (int i = 1; i < E_set.size() - 1; i = i + 2) {
            // add B edges
            int in = E_set[i];
            int out = E_set[i+1];
            if (intermediate[in][0] == -1) intermediate[in][0] = out;
            else if (intermediate[in][1] == -1) intermediate[in][1] = out;
            if (intermediate[out][0] == -1) intermediate[out][0] = in;
            else if (intermediate[out][1] == -1) intermediate[out][1] = in;
        }
    }
}

List* EAX::completeSol() {
    int size = intermediate.size();
    std::vector<List*> sub_tours;
    std::vector<bool> visited(size, false);
    for (int i = 0; i < size; ++i) {
        if (visited[i]) continue;
        List* s = new List();
        int start = i, curr = start, pre = -1, next;
        while (true) {
            visited[curr] = true;
            s->add(new Node(curr, positions[curr][0], positions[curr][1]));
            if (intermediate[curr][0] == pre) next = intermediate[curr][1];
            else next = intermediate[curr][0];
            pre = curr;
            curr = next;

            if (curr == start) break;
        }
        sub_tours.emplace_back(s);
    }

    for (int i = 1; i < sub_tours.size(); ++i) {
        connectTours(sub_tours[0], sub_tours[i]);
    }

    return sub_tours[0];
}


void EAX::connectTours(List *s1, List *s2) {
    Node* pi = s1->head();
    Node* pj = s2->head();
    double best_delta = INT_MAX;
    Node* best_pi = nullptr, *best_pj = nullptr;
    bool which_conn = true;
    for (int i = 0; i < s1->size(); ++i) {
        for (int j = 0; j < s2->size(); ++j) {
            double before = Node::distance(pi, pi->next) + Node::distance(pj, pj->next);
            double after1 = Node::distance(pi, pj) + Node::distance(pi->next, pj->next);
            double after2 = Node::distance(pi, pj->next) + Node::distance(pi, pj->next);
            double delta1 = after1 - before;
            double delta2 = after2 - before;
            if (delta1 < best_delta) {
                best_delta = delta1;
                best_pi = pi;
                best_pj = pj;
                which_conn = true;
            }
            if (delta2 < best_delta) {
                best_delta = delta2;
                which_conn = false;
            }
        }
    }
    // execute the connection
    Node* pi_next = best_pi->next;
    Node* pj_next = best_pj->next;
    if (which_conn) {
        s2->reverse();
        best_pi->next = best_pj;
        best_pj->pre = best_pi;
        pi_next->pre = pj_next;
        pj_next->next = pi_next;
    } else {
        best_pi->next = pj_next;
        pj_next->pre = best_pi;
        pi_next->pre = best_pj;
        best_pj->next = pi_next;
    }
    s1->setSize(s1->size() + s2->size());
}
