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
    intersect(const Ray &ray, double min_t, double &smallest_t_so_far, Vector3d &n) const override;
};

#endif
