#include "BVH.h"

bool BVHNode::intersect(const Ray &ray, double t_min, double &t_max, Vector3d &n) const {
    return box.intersect(ray, t_min, t_max, n) &&
        (right.intersect(ray, t_min, t_max, n) || left.intersect(ray, t_min, t_max, n));
}

bool BVHLeaf::intersect(const Ray &ray, double t_min, double &t_max, Vector3d &n) const {
    return box.intersect(ray, t_min, t_max, n) &&
     triangles.intersect(ray, t_min, t_max, n);
}
