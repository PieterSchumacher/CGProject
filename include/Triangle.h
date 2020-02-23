#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Object.h"
#include "Ray.h"
#include "Eigen"
#include <numeric>
#include <iostream>

using Eigen::Vector3d;
using Eigen::Matrix3d;
using std::vector;

class Triangle : public Object {
  public:
    Matrix3d vertices;
    Matrix3d normals;
    bool intersect(const Ray &ray, double t_min, double &t_max, Vector3d &n) const override;
    void get_normal(const Vector3d &l, Vector3d &n) const override;
};

#endif
