/**
 * GAX.cpp
 * created on : Jan 12 2023
 * author : Z.LEI
 **/

#include "Genetic/Crossover/GAX.hpp"

GAX::GAX() {}
GAX::~GAX() {}

List* GAX::realRun(List *s1, List *s2) {
    int size = s1->size();
    List sc1 = *s1, sc2 = *s2;
    List *s = nullptr;
    int i = -1, k = -1;
    while (i < 0 || k < 0 || i + k > size) {
        i = random->randomInt(size) + 1;  // start from 1
        k = random->randomInt(size) + 1;  // size > 1
    }
    s = &sc1;
    Node *h1 = sc1.head();
    Node *h2 = sc2.head();
    Node *p1 = h1;
    Node *p2 = h2;
    Node *head = s->head();
    Node *p = head;
    int new_size = 1;
    int move = i + 1;
    bool flag = true;
    while(p1 != h1->pre && p2 != h2->pre) {
        p1 = p1->next;
        p2 = p2->next;
        move--;
        if (move == 0) {
            Node *pmove = flag ? p1->pre : p2->pre;
            p->next = pmove;
            pmove->pre = p;
            p = pmove;
            new_size++;
            for (int q = 1; q < k; ++q) {
                if (p != h1->pre && p != h2->pre) {
                    p = p->next;
                    new_size++;
                }
            }
            flag = !flag;
            move = k;
        }
    }
    p->next = head;
    head->pre = p;
    s->setSize(new_size);
    // delete redundant nodes
    std::vector<bool> existed(size, false);
    Node *sp = head;
    for (int i = 0; i < new_size; ++i) {
        if (existed[sp->id]) {
            Node *next = sp->next;
            s->remove(sp);
            sp = next;
        } else {
            existed[sp->id] = true;
            sp = sp->next;
        }
    }
    // insert remaining nodes in sc2
    Node *s2p = s2->head();
    for (int i = 0; i < size; ++i) {
        if (!existed[s2p->id]) {
            sp = head;
            double best_cost = INT_MAX;
            Node* best_p = nullptr;
            for (int j = 0; j < size; ++j) {
                double cost = Node::distance(sp, s2p) + Node::distance(s2p, sp->next);
                if (cost < best_cost) {
                    best_cost = cost;
                    best_p = sp;
                }
                sp = sp->next;
            }
            Node *n = new Node(*s2p);
            s->add(n, best_p);
            existed[s2p->id] = true;
        }
        s2p = s2p->next;
    }

    List* offspring = new List(*s);
    return offspring;
}