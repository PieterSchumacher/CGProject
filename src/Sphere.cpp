#include <iostream>
#include "Sphere.h"
#include "Ray.h"
#include "../Eigen/Core"
using Eigen::Vector3d;
bool
Sphere::intersect(const Ray &ray, const double min_t, double &t, Eigen::Vector3d &n) const
{
//    std::cout << "origin of ray: " << ray.origin << "\n";
//    std::cout << "direction of ray: " << ray.direction << "\n";
//    std::cout << "center of sphere: : " << center << "\n";
//    std::cout << "vector oc: " << oc << "\n";
//    std::cout << "double loc: " << loc << "\n";
//    std::cout << "discriminant: " << discriminant << "\n";
    Vector3d oc = ray.origin - center;
    double loc = ray.direction.dot(oc);
    double discriminant = pow(loc,2.0) - (oc.squaredNorm() - pow(radius,2.0));
    if (discriminant < 1e-6) {
        return false;
    }
    double sqrt_d = sqrt(discriminant);
    t = fmin(-loc - sqrt_d,
             -loc + sqrt_d);
//    std::cout << t << "\n";
    if (t >= min_t) {
        n = ((ray.origin + t * ray.direction) - center) / radius;
        return true;
    }
    return false;
}

