#ifndef RAY_H
#define RAY_H

#include "Eigen"

using Eigen::Vector3d;

struct Ray {
  Vector3d x;
  Vector3d wo;
};

#endif
