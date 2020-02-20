#ifndef SPHERE_H
#define SPHERE_H

#include "Object.h"
#include "../Eigen/Core"

class Sphere : public Object
{
  public:
    Eigen::Vector3d center;
    double radius;
  public:
    bool
    intersect(const Ray &ray, double min_t, double &smallest_t_so_far, Eigen::Vector3d &n) const override;
};

#endif
