#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Object.h"
#include "../Eigen/Core"

using Eigen::Vector3d;

class Triangle : public Object {
  public:
    // A triangle has three corners
    std::tuple<Vector3d, Vector3d, Vector3d> corners;
    bool
    intersect(const Ray &ray, double t_min, double &t_max) const override;
};

#endif
