#include "Plane.h"
#include "Ray.h"

auto Plane::intersect(const Ray &ray, double t_min, double &t_max, Vector3d &n, rgb &fr) const -> bool {
    double t = (point - ray.x).dot(normal) /  ray.wo.dot(normal);
    if (t < t_min || t_max < t) {
        return false;
    }
    t_max = t;
    n = normal;
    fr = material->kd;
    return true;
}


auto Plane::v_min() const -> Vector3d {
    return Eigen::Vector3d();
}

auto Plane::v_max() const -> Vector3d {
    return Eigen::Vector3d();
}

auto Plane::center() const -> Vector3d {
    return Eigen::Vector3d();
}
