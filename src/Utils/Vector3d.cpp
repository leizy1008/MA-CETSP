/**
 * Vector3d.cpp
 * created on : Nov 30 2022
 * author : Z.LEI
 **/

#include "Utils/Vector3d.hpp"

Vector3d::Vector3d() {}
Vector3d::~Vector3d() {}

Vector3d::Vector3d(double dx, double dy, double dz) {
    x = dx;
    y = dy;
    z = dz;
}

void Vector3d::set(double dx, double dy, double dz) {
    x = dx;
    y = dy;
    z = dz;
}

Vector3d Vector3d::operator + (const Vector3d& v) const {
    return Vector3d(x + v.x, y + v.y, z + v.z);
}

Vector3d Vector3d::operator - (const Vector3d& v) const {
    return Vector3d(x - v.x, y - v.y, z - v.z);
}

Vector3d Vector3d::Scalar(double c) const {
    return Vector3d(c*x, c*y, c*z);
}

double Vector3d::Dot(const Vector3d& v) const {
    return x * v.x + y * v.y + z * v.z;
}

Vector3d Vector3d::Cross(const Vector3d& v) const {
    return Vector3d(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
}

bool Vector3d::operator == (const Vector3d& v) const {
    if (abs(x - v.x) < EPSILON && abs(y - v.y) < EPSILON && abs(z - v.z) < EPSILON) return true;
    return false;
}
