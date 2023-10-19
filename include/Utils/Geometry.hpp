/**
 * Geometry.hpp
 * created on : Nov 30 2022
 * author : Z.LEI
 **/

#ifndef CETSP_GEOMETRY_HPP
#define CETSP_GEOMETRY_HPP

#include "Defs.hpp"
#include "Vector3d.hpp"
#include <cmath>

class Geometry {
public:
    Geometry() {}
    ~Geometry() {}

    static bool inCircle(double x, double y, double x0, double y0, double r) {
        return std::pow(x-x0, 2) + std::pow(y-y0, 2) <= std::pow(r, 2) + EPSILON;
    }

    static std::vector<std::vector<double>> solveLineIntersectSphere(double x1, double y1, double x2, double y2, double x0, double y0, double R) {
        std::vector<Vector3d> points;
        Vector3d A(x1, y1, 0);
        Vector3d B(x2, y2, 0);
        Vector3d O(x0, y0, 0);
        Vector3d V = B - A;
        // coefficient
        double a = (V.x * V.x) + (V.y * V.y) + (V.z * V.z);
        double b = 2 * V.x * (A.x - O.x) + 2 * V.y * (A.y - O.y) + 2 * V.z * (A.z - O.z);
        double c = ((A.x - O.x)*(A.x - O.x) + (A.y - O.y) * (A.y - O.y) + (A.z - O.z) * (A.z - O.z)) - R * R;

        std::vector<double> t;
        solveQuadratics(a, b, c, t);
        for (double it : t)  {
            if (it >= 0 && it <= 1) {
                points.push_back(A + V.Scalar(it));
            }
        }
        std::vector<std::vector<double>> intersections;
        for (Vector3d it : points) {
            intersections.emplace_back(std::vector<double> {it.x, it.y});
        }
        return intersections;
    }

    static void solveQuadratics(double a, double b, double c, std::vector<double>& t) {
        double delta = b * b - 4 * a * c;
        if (delta < 0) {
            return;
        }
        if (abs(delta) < EPSILON) {
            t.push_back(-b / (2 * a));
        } else {
            t.push_back((-b + std::sqrt(delta)) / (2 * a));
            t.push_back((-b - std::sqrt(delta)) / (2 * a));
        }
    }

    static double EucDistance(double x1, double y1, double x2, double y2) {
        return std::sqrt(std::pow(x1 - x2, 2) + std::pow(y1 - y2, 2));
    }
};

#endif //CETSP_GEOMETRY_HPP
