#ifndef POINTLIGHT_H
#define POINTLIGHT_H
#include "Light.h"
#include "../Eigen/Core"
class PointLight : public Light {
  public:
    Eigen::Vector3d p;
    void direction(
      const Eigen::Vector3d & q, Eigen::Vector3d & d, double & max_t) const override;
};
#endif

