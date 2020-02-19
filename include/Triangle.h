#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Object.h"
#include "../Eigen/Core"

class Triangle : public Object
{
  public:
    // A triangle has three corners
    std::tuple< Eigen::Vector3d, Eigen::Vector3d, Eigen::Vector3d> corners;
    bool
    intersect(const Ray &ray, double min_t, double &t, Eigen::Vector3d &n) const override;
};

#endif
