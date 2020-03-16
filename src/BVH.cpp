#include <memory>

#include <utility>

#include "BVH.h"

auto BVH::v_min() const -> Vector3d {
    return box.v_min();
}

auto BVH::v_max() const -> Vector3d {
    return box.v_max();
}

auto BVH::center() const -> Vector3d {
    return box.center();
}

auto BVHNode::intersect(const Ray &ray, double t_min, double &t_max, Vector3d &n) const -> bool {
    return box.intersect(ray, t_min, t_max) &&
          (right->intersect(ray, t_min, t_max, n) | left->intersect(ray, t_min, t_max, n));
}

auto BVHLeaf::intersect(const Ray &ray, double t_min, double &t_max, Vector3d &n) const -> bool {
    return box.intersect(ray, t_min, t_max) &&
           find_nearest_intersection(objects, ray, t_min, t_max, n);
}

auto top_down(vector<shared_ptr<Object>> &objects, const unsigned int splitType) -> shared_ptr<BVH> {
    shared_ptr<BVH> bvh_ptr;
    Vector3d mean_centroid(0,0,0);
    Vector3d v_min(1e6,1e6,1e6);
    Vector3d v_max(-1e6, -1e6, -1e6);
    for (const shared_ptr<Object> &object : objects) {
        v_min = v_min.cwiseMin(object->v_min());
        v_max = v_max.cwiseMax(object->v_max());
        mean_centroid += object->center();
    }
    Vector3d dv(1e-7, 1e-7, 1e-7);
    AABB convex(v_min - dv, v_max + dv);
    mean_centroid /= fmax(1,objects.size());
    // Either split in two nodes or make a leaf
    if (objects.size() > 6) {
        vector<shared_ptr<Object>> left;
        vector<shared_ptr<Object>> right;
        for (const shared_ptr<Object> &object : objects) {
            if (object->center()(splitType) < mean_centroid(splitType)) {
                left.push_back(object);
            } else {
                right.push_back(object);
            }
        }
        shared_ptr<BVH> left_node = top_down(left, static_cast<const unsigned int>(fmod(splitType + 1, 3)));
        shared_ptr<BVH> right_node = top_down(right, static_cast<const unsigned int>(fmod(splitType + 1, 3)));
        bvh_ptr = shared_ptr<BVH>(new BVHNode(right_node, left_node));
    } else {
        bvh_ptr = shared_ptr<BVH>(new BVHLeaf(objects));
    }
    bvh_ptr->box = std::move(convex);
    return bvh_ptr;
}
