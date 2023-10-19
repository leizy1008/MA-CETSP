/**
 * AlhazenProblem.hpp
 * created on : Nov 30 2022
 * author : Z.LEI
 **/

#ifndef CETSP_ALHAZENPROBLEM_HPP
#define CETSP_ALHAZENPROBLEM_HPP

#include "Vector3d.hpp"
#include <cmath>

class AlhazenProblem {
private:
    Vector3d A;
    Vector3d B;
    Vector3d O;
    double R;
    void findBoundary(double& a, double& b);
    double bisection(double a, double b);
    double functionPrime(double angle);
public:
    AlhazenProblem(double x1, double y1, double x2, double y2, double x0, double y0, double R);
    ~AlhazenProblem();
    std::vector<double> solve();
};


#endif //CETSP_ALHAZENPROBLEM_HPP
