#ifndef PLANE_H
#define PLANE_H

#include "Object.h"
#include "../Eigen/Core"

using Eigen::Vector3d;

class Plane : public Object {
  public:
    Vector3d point;
    Vector3d normal;
    bool intersect(const Ray &ray, double min_t, double &smallest_t_so_far, Eigen::Vector3d &n) const override;
};

#endif
