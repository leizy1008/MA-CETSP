/**
 * Vector3d.hpp
 * created on : Nov 30 2022
 * author : Z.LEI
 **/

#ifndef CETSP_VECTOR3D_HPP
#define CETSP_VECTOR3D_HPP

#include "Defs.hpp"

class Vector3d {
public:
    double x, y, z;
    Vector3d();
    ~Vector3d();
    Vector3d(double dx, double dy, double dz);
    void set(double dx, double dy, double dz);
    Vector3d operator + (const Vector3d& v) const;
    Vector3d operator - (const Vector3d& v) const;
    Vector3d Scalar(double c) const;
    double Dot(const Vector3d& v) const;
    Vector3d Cross(const Vector3d& v) const;
    bool operator == (const Vector3d& v) const;
};

#endif //CETSP_VECTOR3D_HPP
