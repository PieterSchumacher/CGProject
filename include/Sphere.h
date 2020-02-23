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
    intersect(const Ray &ray, double t_min, double &t_max, Vector3d &n) const override;
    void get_normal(const Vector3d &l, Vector3d &n) const override;
};

#endif
