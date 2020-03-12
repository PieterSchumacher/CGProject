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
using std::move;

class Triangle : public Object {
  public:
    Matrix3d vertices;
    Matrix3d normals;
    ~Triangle() {};
    Triangle(Matrix3d &vertices, Matrix3d &normals);
    bool intersect(const Ray &ray, double t_min, double &t_max, Vector3d &n) const override;
    Vector3d v_min() const override;
    Vector3d v_max() const override;
    Vector3d center() const override;
};

#endif
