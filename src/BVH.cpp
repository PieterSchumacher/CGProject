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

auto BVHNode::intersect(const Ray &ray, double t_min, double &t_max, Vector3d &n, rgb &fr) const -> bool {
    return box.intersect(ray, t_min, t_max) &&
          (ray.wo(splitType) < 0 ? right->intersect(ray, t_min, t_max, n, fr) | left->intersect(ray, t_min, t_max, n, fr)
                                 : left->intersect(ray, t_min, t_max, n, fr) | right->intersect(ray, t_min, t_max, n, fr));
}

auto BVHLeaf::intersect(const Ray &ray, double t_min, double &t_max, Vector3d &n, rgb &fr) const -> bool {
    return box.intersect(ray, t_min, t_max) &&
            find_nearest_intersection(leaf_objects, ray, t_min, t_max, n, fr);
}

auto top_down(vector<shared_ptr<Object>> &leaf_objects, const unsigned int splitType) -> shared_ptr<BVH> {
    shared_ptr<BVH> bvh_ptr;
    Vector3d mean_centroid(0,0,0);
    Vector3d v_min(1e6,1e6,1e6);
    Vector3d v_max(-1e6, -1e6, -1e6);
    for (const shared_ptr<Object> &object : leaf_objects) {
        v_min = v_min.cwiseMin(object->v_min());
        v_max = v_max.cwiseMax(object->v_max());
        mean_centroid += object->center();
    }
    Vector3d dv(1e-6, 1e-6, 1e-6);
    AABB convex(v_min - dv, v_max + dv);
    mean_centroid /= fmax(1,leaf_objects.size());
    // Either split in two nodes or make a leaf
    if (leaf_objects.size() > 1) {
        vector<shared_ptr<Object>> left;
        vector<shared_ptr<Object>> right;
        for (const shared_ptr<Object> &object : leaf_objects) {
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
        bvh_ptr = shared_ptr<BVH>(new BVHLeaf(leaf_objects));
    }
    bvh_ptr->box = std::move(convex);
    bvh_ptr->splitType = splitType;
    return bvh_ptr;
}
