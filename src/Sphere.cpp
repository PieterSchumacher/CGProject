#include <iostream>
#include "Sphere.h"
#include "Ray.h"
#include "../Eigen/Core"
using Eigen::Vector3d;
bool Sphere::intersect(const Ray &ray, const double min_t, double &t, Eigen::Vector3d &n) const {
    Vector3d oc = ray.origin - center;
    double loc = ray.direction.dot(oc);
    double discriminant = pow(loc,2.0) - (oc.squaredNorm() - pow(radius,2.0));
    if (discriminant < 1e-6) {
        return false;
    }
    double sqrt_d = sqrt(discriminant);
    t = fmin(-loc - sqrt_d,
             -loc + sqrt_d);
    if (t >= min_t) {
        n = ((ray.origin + t * ray.direction) - center) / radius;
        return true;
    }
    return false;
}

