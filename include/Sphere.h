#ifndef SPHERE_H
#define SPHERE_H

#include "Object.h"
#include "../Eigen/Core"

using Eigen::Vector3d;

class Sphere : public Object {
  public:
    Vector3d center;
    double radius;
  public:
    bool
    intersect(const Ray &ray, double min_t, double &smallest_t_so_far, Vector3d &n) const override;
};

#endif
