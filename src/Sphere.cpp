#include "Sphere.h"
#include "Ray.h"
using Eigen::Vector3d;
bool Sphere::intersect(const Ray &ray, double min_t, double &smallest_t_so_far, Vector3d &n) const {
    Vector3d oc = ray.eye - center;
    double loc = ray.direction.dot(oc);
    double discriminant = pow(loc,2.0) - (oc.squaredNorm() - pow(radius,2.0));
    if (discriminant < 1e-6) {
        return false;
    }
    double sqrt_d = sqrt(discriminant);
    double t = fmin(-loc - sqrt_d,
                    -loc + sqrt_d);
    if (t < smallest_t_so_far && t >= min_t) {
        smallest_t_so_far = t;
        n = ((ray.eye + t * ray.direction) - center) / radius;
        return true;
    }
    return false;
}

