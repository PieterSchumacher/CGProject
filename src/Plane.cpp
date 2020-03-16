#include "Plane.h"
#include "Ray.h"

auto Plane::intersect(const Ray &ray, double t_min, double &t_max, Vector3d &n) const -> bool {
    double ln = ray.direction.dot(normal);
    if (ln > -1e-12) {
        return false;
    }
    double d = (point - ray.eye).dot(normal) / ln;
    if (d < t_min || t_max < d) {
        return false;
    }
    t_max = d;
    n = normal;
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
