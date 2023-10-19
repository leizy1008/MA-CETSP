/**
 * ListAdapter.cpp
 * created on : Jan 03 2023
 * author : Z.LEI
 **/

#include "LocalSearch/ListAdapter.hpp"

ListAdapter::ListAdapter() {}
ListAdapter::~ListAdapter() {}

List* ListAdapter::real2Reduced(List* real_list) {
    // real_list->print();
    int size = real_list->size();
    Node* p = real_list->head();
    for (int i = 0; i < size; ++i) {
        double x = p->x, y = p->y;
        if (i == 0 || !(x == p->pre->x && y == p->pre->y)) {
            nodes.emplace_back(std::vector<int> {p->id});
            positions.emplace_back(std::vector<double> {x, y});
            p = p->next;
        } else {
            nodes[nodes.size() - 1].emplace_back(p->id);
            p = p->next;
            // delete redundant nodes
            real_list->remove(p->pre);
        }
    }

    // update id
    p = real_list->head();
    for (int i = 0; i < real_list->size(); ++i) {
        p->id = i;
        p = p->next;
    }
    // real_list->print();
    if (LOG) {
        std::cout << "ListAdapter solutions size before and after : " << size << " " << real_list->size() << std::endl;
    }
    return real_list;
}

List* ListAdapter::reduced2Real(List* reduced_list) {
    // reduced_list->print();
    int size = reduced_list->size();
    Node* p = reduced_list->head();
    for (int i = 0; i < size; ++i) {
        int index = p->id;
        Node* next = p->next;
        p->id = nodes[index][0];
        for (int j = 1; j < nodes[index].size(); ++j) {
            reduced_list->add(new Node(nodes[index][j], positions[index][0], positions[index][1]), p);
        }
        p = next;
    }
    // reduced_list->print();
    return reduced_list;
}