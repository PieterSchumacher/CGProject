#include <iostream>
#include "PointLight.h"

void PointLight::direction(
  const Vector3d & q, Vector3d & d, double & max_t) const {
    d = p - q;
}

rgb PointLight::Le(const Vector3d &n, const Vector3d &x, const vector<shared_ptr<Object>> &objects) const {
    Vector3d l;
    double max_t;
    this->direction(x, l, max_t);
    double cosTheta = n.dot(l) / l.norm();
    rgb I = this->I;
    return cosTheta > 1e-12 && !find_intersection(objects, {l + x, -l.normalized()}, l.norm() - 1e-12) ?
        I * cosTheta :
        rgb(0,0,0);
}
