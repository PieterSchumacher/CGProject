#ifndef POINTLIGHT_H
#define POINTLIGHT_H
#include "Light.h"

#include <utility>
#include "../Eigen/Core"

using Eigen::Vector3d;
using std::move;

class PointLight : public Light {
private:
    Vector3d p;
public:
    PointLight(Vector3d p) : p(move(p)) {};
    auto wi(const Vector3d &x) const -> Vector3d override;
    auto samples(const Vector3d &x) const -> vector<Vector3d> override;
};
#endif

