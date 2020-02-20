#ifndef RAY_H
#define RAY_H

#include "../Eigen/Core"

using Eigen::Vector3d;

struct Ray {
  Vector3d eye;
  Vector3d direction;
};

#endif
