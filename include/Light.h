#ifndef LIGHT_H
#define LIGHT_H
#include "../Eigen/Core"
#include "RGB.h"

using Eigen::Vector3d;

class Light {
  public:
    // Color (intensities)
    rgb I{};
    virtual ~Light() {};
    virtual void direction(
      const Vector3d & q,
      Vector3d & d,
      double & max_t) const =0;
};
#endif
