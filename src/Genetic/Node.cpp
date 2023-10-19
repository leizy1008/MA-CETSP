/**
 * Node.cpp
 * created on : Nov 30 2022
 * author : Z.LEI
 **/

#include "Genetic/Node.hpp"

Node::Node(int id, double x, double y) {
    this->id = id;
    this->x = x;
    this->y = y;
    this->pre = nullptr;
    this->next = nullptr;
}

Node::Node(const Node& n) {
    this->id = n.id;
    this->x = n.x;
    this->y = n.y;
    this->pre = nullptr;
    this->next = nullptr;
}

Node::~Node() {}

Node& Node::operator=(Node& n) {
    this->id = n.id;
    this->x = n.x;
    this->y = n.y;
    this->pre = nullptr;
    this->next = nullptr;
    return *this;
}

double Node::distance(Node *n1, Node *n2) {
    double x1 = n1->x, y1 = n1->y;
    double x2 = n2->x, y2 = n2->y;
    return Geometry::EucDistance(x1, y1, x2, y2);
}

void Node::swap(Node *n1, Node *n2) {
    std::swap(n1->id, n2->id);
    std::swap(n1->x, n2->x);
    std::swap(n1->y, n2->y);
}