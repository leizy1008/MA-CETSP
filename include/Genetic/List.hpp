/**
 * List.hpp
 * created on : Nov 30 2022
 * author : Z.LEI
 **/

#ifndef CETSP_LIST_HPP
#define CETSP_LIST_HPP

#include "Node.hpp"
#include <vector>
#include <iostream>
#include <numeric>
#include <climits>

class List {
private:
    int _size;
    Node* _head;
    double value;
    double distance;    // distance to population
    double fitness;     // value and min distance
public:
    List();
    List(const List& s);
    ~List();
    List& operator=(List& s);
    void add(Node* node);
    void add(Node* node, Node* pos);
    void remove(Node *pos);
    void reverse();
    void reverse(Node* begin, Node* end);
    Node* head();
    int size();
    void print();
    double getValue();
    double getDistance();
    double getFitness();
    void setValue(double value);
    void setSize(int size);
    void setHead(Node* p);
    void setDistance(double distance);
    void setFitness(double fitness);
    void evaluate();
};

#endif // CETSP_LIST_HPP
