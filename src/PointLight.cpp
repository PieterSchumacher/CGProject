#include <iostream>
#include "PointLight.h"

auto PointLight::wi(const Vector3d &x) const -> Vector3d {
   return p - x;
}

auto PointLight::samples(const Vector3d &x) const -> vector<Vector3d> {
    return vector<Vector3d>({wi(x)});
}
