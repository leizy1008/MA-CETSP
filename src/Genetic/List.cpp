/**
 * List.cpp
 * created on : Nov 30 2022
 * author : Z.LEI
 **/

#include "Genetic/List.hpp"

List::List() {
    _head = nullptr;
    _size = 0;
    value = 0;
    distance = INT_MAX;
    fitness = 0;
}

List::List(const List& s) {
    _head = nullptr;
    _size = 0;
    value = s.value;
    distance = s.distance;
    fitness = s.fitness;
    Node* sp = s._head;
    int s_size = s._size;
    for (int i = 0; i < s_size; ++i) {
        Node *node = new Node(sp->id, sp->x, sp->y);
        add(node);
        sp = sp->next;
    }
}

List::~List() {}

List& List::operator=(List& s) {
    if (this == &s) {
        return *this;
    }
    _head = nullptr;
    _size = 0;
    value = s.value;
    distance = s.distance;
    fitness = s.fitness;

    Node* sp = s._head;
    int s_size = s._size;
    for (int i = 0; i < s_size; ++i) {
        Node *node = new Node(sp->id, sp->x, sp->y);
        add(node);
        sp = sp->next;
    }
    return *this;
}

void List::add(Node* node) {
    if (_head == nullptr) {
        _head = node;
        _head->pre = node;
        _head->next = node;

    } else {
        Node* p = _head->pre;
        p->next = node;
        _head->pre = node;
        node->pre = p;
        node->next = _head;
    }
    _size++;
}

void List::add(Node* node, Node* pos) {
    Node* next = pos->next;
    pos->next = node;
    next->pre = node;
    node->next = next;
    node->pre = pos;
    _size++;
}

void List::remove(Node *pos) {
    Node* pre = pos->pre;
    Node* next = pos->next;
    pre->next = next;
    next->pre = pre;
    if (pos == _head) {
        _head = next;
    }
    delete pos;
    _size--;
}

void List::reverse(Node* begin, Node* end) {
    Node* p = begin;
    while (p != end) {
        // reverse i->j-1
        Node* pre = p->pre;
        Node* next = p->next;
        p->next = pre;
        p->pre = next;
        p = next;
    }
}

void List::reverse() {
    Node* p = head();
    for (int i = 0; i < size(); ++i) {
        Node* pre = p->pre;
        Node* next = p->next;
        p->next = pre;
        p->pre = next;
        p = next;
    }
}

Node* List::head() {
    return _head;
}

int List::size() {
    return _size;
}

void List::print() {
    Node* p = _head;
    for (int i = 0; i < _size; ++i) {
        std::cout << p->id << ",";
        p = p->next;
    }
    std::cout << std::endl;
}

double List::getValue() {
    return value;
}

double List::getDistance() {
    return distance;
}

double List::getFitness() {
    return fitness;
}

void List::setValue(double value) {
    this->value = value;
}

void List::setSize(int size) {
    this->_size = size;
}

void List::setHead(Node* p) {
    this->_head = p;
}

void List::setDistance(double distance) {
    this->distance = distance;
}

void List::setFitness(double fitness) {
    this->fitness = fitness;
}

void List::evaluate() {
    Node *p = head();
    double value = 0;
    for (int i = 0; i < size(); ++i) {
        value += Node::distance(p, p->next);
        p = p->next;
    }
    setValue(value);
}
