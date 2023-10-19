/**
 * Greed.cpp
 * created on : March 03 2022
 * author : Z.LEI
 **/

#include "LocalSearch/Greed.hpp"

Greed::Greed(std::string greed_type) {
    this->greed_type = greed_type;
}
Greed::~Greed() {}

void Greed::setContext(Centers &centers) {
    this->centers = centers;
}

void Greed::run(List* &s) {
    auto start = std::chrono::high_resolution_clock::now();

    List* ns = new List(*s);
    // size must be equal to or greater than 3
    if (ns->size() < 3) return;
    double value = 0;
    Node* p = ns->head()->next;
    while (p != ns->head()) {
        int id = p->id;
        value += updatePosition(p, centers[id][0], centers[id][1], centers[id][2]);
        p = p->next;
    }
    value += Node::distance(p->pre, p);
    ns->setValue(value);
    if (ns->getValue() < s->getValue()) {
        delete s;
        s = ns;
    } else if (LOG){
        std::cout << "[GREED] not accept" << std::endl;
    };

    auto end = std::chrono::high_resolution_clock::now();
    if (LOG) std::cout << "greed solution : " << s->getValue() << " time : " << std::chrono::duration<double> (end - start).count() << " s" << std::endl;
}

double Greed::updatePosition(Node* node, double x0, double y0, double r) {
    Node* pre = node->pre;
    Node* next = node->next;
    double x1 = pre->x, y1 = pre->y, x2 = next->x, y2 = next->y;
    // judge points in or out circle
    bool in_circle1 = Geometry::inCircle(x1, y1, x0, y0, r);
    bool in_circle2 = Geometry::inCircle(x2, y2, x0, y0, r);
    if (in_circle1 && in_circle2) {
        if (greed_type == "SQUEEZE") {
            node->x = x1, node->y = y1;
            return 0;
        } else if (greed_type == "SPARSE") {
            node->x = (x1 + x2) / 2, node->y = (y1 + y2) / 2;
            return Node::distance(pre, node);
        }
    } else if (in_circle1) {
        node->x = x1, node->y = y1;
        return 0;
    } else if (in_circle2) {
        node->x = x2, node->y = y2;
        return Node::distance(pre, node);
    } else {
        auto intersections = Geometry::solveLineIntersectSphere(x1, y1, x2, y2, x0, y0, r);
        if (intersections.size() == 2) {
            node->x = intersections[0][0];
            node->y = intersections[0][1];
        } else if (intersections.size() == 1){
            node->x = intersections[0][0];
            node->y = intersections[0][1];
        } else {
            AlhazenProblem ap(x1, y1, x2, y2, x0, y0, r);
            auto position = ap.solve();
            node->x = position[0];
            node->y = position[1];
        }
        return Node::distance(pre, node);
    }
    return Node::distance(pre, node);
}

std::vector<double> Greed::approxPosition(double x0, double y0, double r, Node* pre, Node* next) {
    double x, y;
    double x1 = pre->x, y1 = pre->y, x2 = next->x, y2 = next->y;
    // judge points in or out circle
    bool in_circle1 = Geometry::inCircle(x1, y1, x0, y0, r);
    bool in_circle2 = Geometry::inCircle(x2, y2, x0, y0, r);
    if (in_circle1 && in_circle2) {
        x = x1, y = y1;
        if (greed_type == "SQUEEZE") {
            x = x1, y = y1;
        } else if (greed_type == "SPARSE") {
            x = (x1 + x2) / 2, y = (y1 + y2) / 2;
        }
    } else if (in_circle1) {
        x = x1, y = y1;
    } else if (in_circle2) {
        x = x2, y = y2;
    } else {
        auto intersections = Geometry::solveLineIntersectSphere(x1, y1, x2, y2, x0, y0, r);
        if (intersections.size() == 2) {
            x = (intersections[0][0] + intersections[1][0]) / 2;
            y = (intersections[0][1] + intersections[1][1]) / 2;
        } else if (intersections.size() == 1){
            x = intersections[0][0];
            y = intersections[0][1];
        } else {
            double mid_point_x = (pre->x + next->x) / 2;
            double mid_point_y = (pre->y + next->y) / 2;
            auto intersections = Geometry::solveLineIntersectSphere(mid_point_x, mid_point_y, x0, y0, x0, y0, r);
            if (intersections.size() != 1) std::cout << "ERROR : only one intersection !!!" << std::endl;
            x = intersections[0][0];
            y = intersections[0][1];
        }
    }
    return std::vector<double> {x, y};
}

bool Greed::inLine(double x0, double y0, double r, Node* pre, Node* next) {
    double x1 = pre->x, y1 = pre->y, x2 = next->x, y2 = next->y;
    // in circle
    bool in_circle1 = Geometry::inCircle(x1, y1, x0, y0, r);
    bool in_circle2 = Geometry::inCircle(x2, y2, x0, y0, r);
    if (in_circle1 || in_circle2) return true;
    // have intersections
    auto intersections = Geometry::solveLineIntersectSphere(x1, y1, x2, y2, x0, y0, r);
    if (intersections.size() > 0) return true;
    return false;
}
