/**
 * Greed.hpp
 * created on : March 03 2022
 * author : Z.LEI
 **/

#ifndef CETSP_GREED_HPP
#define CETSP_GREED_HPP

#include "Defs.hpp"
#include "Genetic/List.hpp"
#include "Geometry.hpp"
#include "Utils/AlhazenProblem.hpp"
#include <chrono>

class Greed {
private:
    Centers centers;
    std::string greed_type;
public:
    Greed(std::string greed_type);
    ~Greed();
    void setContext(Centers &centers);
    void run(List *&s);
    double updatePosition(Node *node, double x0, double y0, double r);
    std::vector<double> approxPosition(double x0, double y0, double r, Node *pre, Node *next);
    bool inLine(double x0, double y0, double r, Node* pre, Node* next);
};

#endif //CETSP_GREED_HPP
