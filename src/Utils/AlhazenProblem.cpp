/**
 * AlhazenProblem.cpp
 * created on : Nov 30 2022
 * author : Z.LEI
 **/

#include "Utils/AlhazenProblem.hpp"

AlhazenProblem::AlhazenProblem(double x1, double y1, double x2, double y2, double x0, double y0, double R) :
        A(x1, y1, 0), B(x2, y2, 0), O(x0, y0, 0), R(R) {}

AlhazenProblem::~AlhazenProblem() {}

std::vector<double> AlhazenProblem::solve() {
    double a = -1, b = -1;
    double angle;
    findBoundary(a, b);
    if (a == b) {
        angle = a;
    } else {
        angle = bisection(a, b);
    }
    double x = O.x + R * cos(angle);
    double y = O.y + R * sin(angle);
    double z = 0;
    return std::vector<double> {x, y, z};
}

void AlhazenProblem::findBoundary(double& a, double& b) {
    std::vector<double> keys = {0, PI / 2, PI, 3 * PI / 2, 2 * PI};
    std::vector<double> values = {functionPrime(0), functionPrime(PI / 2), functionPrime(PI), functionPrime(3 * PI / 2), functionPrime(2 * PI)};
    for (int i = 0; i < values.size() - 1; ++i) {
        if (abs(values[i]) < EPSILON && functionPrime(keys[i] - PI / 2) < 0 && functionPrime(keys[i] + PI / 2) > 0) {
            a = keys[i], b = keys[i];
            return;
        }
    }
    for (int i = 0; i < values.size() - 1; ++i) {
        if (values[i] * values[i+1] < 0) {
            if (values[i] < 0 && values[i+1] > 0) {
                a = keys[i], b = keys[i+1];
                return;
            }
        }
    }
}

double AlhazenProblem::bisection(double a, double b) {
    double mid, value;
    bool found = false;
    int i = 0;
    while (!found) {
        if (i > 100) break;
        mid = a + (b - a) / 2 ;
        value = functionPrime(mid);
        if (value > EPSILON) {
            b = mid;
        } else if (value < -EPSILON) {
            a = mid;
        } else {
            found = true;
        }
        i++;
    }
    return mid;
}

double AlhazenProblem::functionPrime(double angle) {
    double expr1 = R * ((O.y - A.y) * cos(angle) - (O.x - A.x) * sin(angle)) / sqrt(pow(O.x + R * cos(angle) - A.x, 2) + pow(A.y + R * sin(angle) - A.y, 2));
    double expr2 = R * ((O.y - B.y) * cos(angle) - (O.x - B.x) * sin(angle)) / sqrt(pow(O.x + R * cos(angle) - B.x, 2) + pow(B.y + R * sin(angle) - B.y, 2));
    return expr1 + expr2;
}