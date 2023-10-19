/**
 * Node.hpp
 * created on : Nov 30 2022
 * author : Z.LEI
 **/

#ifndef CETSP_NODE_HPP
#define CETSP_NODE_HPP

#include "Utils/Geometry.hpp"
#include <cmath>
#include <algorithm>

class Node {
public:
    int id;
    double x, y;
    Node* pre, *next;
    Node(int id, double x, double y);
    Node(const Node& n);
    ~Node();
    Node& operator=(Node& n);
    static double distance(Node *n1, Node *n2);     // calculate the distance between two nodes
    static void swap(Node *n1, Node *n2);           // swap the info between two nodes
};

#endif //CETSP_NODE_HPP
