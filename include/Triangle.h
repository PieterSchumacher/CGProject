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
    ~Triangle() override = default;
    Triangle(Matrix3d &vertices, Matrix3d &normals);
    auto intersect(const Ray &ray, double t_min, double &t_max, Vector3d &n) const -> bool override;
    auto v_min() const -> Vector3d override;
    auto v_max() const -> Vector3d override;
    auto center() const -> Vector3d override;
};

#endif
