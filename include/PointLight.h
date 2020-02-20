#ifndef POINTLIGHT_H
#define POINTLIGHT_H
#include "Light.h"
#include "../Eigen/Core"

using Eigen::Vector3d;

class PointLight : public Light {
  public:
    Vector3d p;
    void direction(
      const Vector3d & q, Vector3d & d, double & max_t) const override;
};
#endif

