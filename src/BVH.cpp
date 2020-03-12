#include <memory>

#include <utility>

#include "BVH.h"

Vector3d BVH::v_min() const {
    return box.v_min();
}

Vector3d BVH::v_max() const {
    return box.v_max();
}

Vector3d BVH::center() const {
    return box.center();
}

bool BVHNode::intersect(const Ray &ray, double t_min, double &t_max, Vector3d &n) const {
    return box.intersect(ray, t_min, t_max) &&
          (right->intersect(ray, t_min, t_max, n) || left->intersect(ray, t_min, t_max, n));
}

bool BVHLeaf::intersect(const Ray &ray, double t_min, double &t_max, Vector3d &n) const {
    return box.intersect(ray, t_min, t_max) &&
           find_nearest_intersection(objects, ray, t_min, t_max, n);
}

void BVHNode::bounding_boxes(vector<shared_ptr<Object>> &objects) const {
    right->bounding_boxes(objects);
    left->bounding_boxes(objects);
}

void BVHLeaf::bounding_boxes(vector<shared_ptr<Object>> &objects) const {
    shared_ptr<AABB> box_copy(new AABB(box.vmin, box.vmax));
    shared_ptr<Material> mat1(new Material());
    mat1->kd = rgb(1.0,1.0,1.0);
    box_copy->material = mat1;
    objects.push_back(box_copy);
}

shared_ptr<BVH> top_down(vector<shared_ptr<Object>> &objects, const unsigned int splitType, Vector3d v_min, Vector3d v_max) {
    // Create the convex AABB
    shared_ptr<BVH> bvh_ptr;
    Vector3d mean_centroid(0,0,0);
    for (const shared_ptr<Object> &object : objects) {
        v_min = v_min.cwiseMin(object->v_min());
        v_max = v_max.cwiseMax(object->v_max());
        mean_centroid += object->center();
    }
    mean_centroid /= fmax(1,objects.size());
        if (mean_centroid(0) > 1e6 || mean_centroid(1) > 1e6 || mean_centroid(2) > 1e6) {
            std::cout << mean_centroid << "\n";
        }
    Vector3d dv(1e-6, 1e-6, 1e-6);
    AABB convex(v_min - dv, v_max + dv);
    // Either split in two nodes or make a leaf
    if (objects.size() > 1) {
        vector<shared_ptr<Object>> left, right;
        for (const shared_ptr<Object> &object : objects) {
            if (object->center()(splitType) < mean_centroid(splitType)) {
                left.push_back(object);
            } else {
                right.push_back(object);
            }
        }
        Vector3d left_vmax = v_max; left_vmax(splitType) = mean_centroid(splitType);
        Vector3d right_vmin = v_min; right_vmin(splitType) = mean_centroid(splitType);
        shared_ptr<BVH> left_node = top_down(left, static_cast<const unsigned int>(fmod(splitType + 1, 3)), v_min, left_vmax);
        shared_ptr<BVH> right_node = top_down(right, static_cast<const unsigned int>(fmod(splitType + 1, 3)), right_vmin, v_max);
        bvh_ptr = shared_ptr<BVH>(new BVHNode(right_node, left_node));
        std::cout << "right_node: \n" << right_node->v_min() << "\n\n" << right_node->v_max() << "\n\n";
        std::cout << "left_node: \n" << left_node->v_min() << "\n\n" << left_node->v_max() << "\n\n";
    } else {
        bvh_ptr = shared_ptr<BVH>(new BVHLeaf(objects));
    }
    bvh_ptr->box = std::move(convex);
    std::cout << "bvh_ptr: \n" << bvh_ptr->v_min() << "\n\n" << bvh_ptr->v_max() << "\n\n";
    return bvh_ptr;
};
