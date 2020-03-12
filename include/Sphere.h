#ifndef SPHERE_H
#define SPHERE_H

#include "Object.h"
#include "../Eigen/Core"

using Eigen::Vector3d;
using std::move;

class Sphere : public Object {
  public:
    Vector3d c;
    double radius;
  public:
    Sphere(double radius, Vector3d center);
    bool intersect(const Ray &ray, double t_min, double &t_max, Vector3d &n) const override;
    Vector3d v_min() const override;
    Vector3d v_max() const override;
    Vector3d center() const override;
};

#endif
