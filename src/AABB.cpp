#include <iostream>
#include "AABB.h"

AABB::AABB(Vector3d v_min, Vector3d v_max) : vmin(move(v_min)), vmax(move(v_max)) {}

auto AABB::v_min() const -> Vector3d {
    return vmin;
}

auto AABB::v_max() const -> Vector3d {
    return vmax;
}

auto AABB::center() const -> Vector3d {
    return (vmax - vmin) / 2;
}

auto AABB::intersect(const Ray &ray, double t_min, double &t_max, Vector3d &n) const -> bool {
    Vector3d T_min = (vmin - ray.eye).cwiseQuotient(ray.direction);
    Vector3d T_max = (vmax - ray.eye).cwiseQuotient(ray.direction);
    double t1 = fmax(fmax(fmin(T_min(0), T_max(0)),
                          fmin(T_min(1), T_max(1))),
                          fmin(T_min(2), T_max(2)));
    if (t1 < t_min || t_max < t1) {
        return false;
    }
    double t2 = fmin(fmin(fmax(T_min(0), T_max(0)),
                          fmax(T_min(1), T_max(1))),
                          fmax(T_min(2), T_max(2)));
    if (t1 > t2) {
        return false;
    }
    t_max = t1;
    Vector3d diff = (vmin - (ray.eye + t_max*ray.direction)).cwiseAbs();
    n = diff(0) < 1e-12 ? Vector3d(-1,0,0)
      : diff(1) < 1e-12 ? Vector3d(0,-1,0)
      :                   Vector3d(0,0,-1);
    return true;
}

auto AABB::intersect(const Ray &ray, double t_min, double t_max) const -> bool {
    Vector3d n;
    return intersect(ray, t_min, t_max, n);
}
