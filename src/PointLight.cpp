#include "PointLight.h"

void PointLight::direction(
  const Vector3d & q, Vector3d & d, double & max_t) const {
    d = p - q;
}
