#ifndef PLANE_H
#define PLANE_H

#include "Object.h"
#include "../Eigen/Core"

class Plane : public Object {
  public:
    // Point on plane
    Eigen::Vector3d point;
    // Normal of plane
    Eigen::Vector3d normal;
    bool intersect(const Ray &ray, double min_t, double &t, Eigen::Vector3d &n) const override;
};

#endif
