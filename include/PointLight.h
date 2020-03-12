#ifndef POINTLIGHT_H
#define POINTLIGHT_H
#include "Light.h"
#include "../Eigen/Core"

using Eigen::Vector3d;

class PointLight : public Light {
  public:
    Vector3d p;
    void direction(const Vector3d & q, Vector3d & d, double & max_t) const override;
    rgb Le(const Vector3d &n, const Vector3d &x, const vector<shared_ptr<Object>> &objects) const override;
};
#endif

