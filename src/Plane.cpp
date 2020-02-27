#include "Plane.h"
#include "Ray.h"
#include <iostream>
bool Plane::intersect(const Ray &ray, double t_min, double &t_max, Vector3d &n) const {
    double ln = ray.direction.dot(normal);
    if (ln < -1e-12) {
        double d = (point - ray.eye).dot(normal) / ln;
        if (t_min <= d && d < t_max) {
            t_max = d;
            n = normal;
            return true; // doesn't work
        }
    }
    return false;
}

