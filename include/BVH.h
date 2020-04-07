#ifndef CGPROJECT_BVH_H
#define CGPROJECT_BVH_H

#include "AABB.h"
#include "Intersection.h"
#include "Triangle.h"
#include <utility>

using std::shared_ptr;
using std::size_t;
using std::tuple;
using std::fmod;
using std::move;
using Eigen::Vector3d;
struct Ray;

// https://en.wikipedia.org/wiki/Composite_pattern
class BVH : public Object {
public:
    AABB box;
    unsigned splitType;
    virtual ~BVH() = default;;
    auto v_min() const -> Vector3d override;
    auto v_max() const -> Vector3d override;
    auto center() const -> Vector3d override;
};

class BVHNode : public BVH {
public:
    BVHNode(shared_ptr<BVH> right, shared_ptr<BVH> &left) : right(move(right)), left(move(left)) {};
    shared_ptr<BVH> right;
    shared_ptr<BVH> left;
    auto intersect(const Ray &ray, double t_min, double &t_max, Vector3d &n, rgb &fr) const -> bool override;
};

class BVHLeaf : public BVH {
public:
    explicit BVHLeaf(vector<shared_ptr<Object>> new_objects) : leaf_objects(move(new_objects)) {};
    vector<shared_ptr<Object>> leaf_objects;
    auto intersect(const Ray &ray, double t_min, double &t_max, Vector3d &n, rgb &fr) const -> bool override;
};

auto top_down(vector<shared_ptr<Object>> &objects, const unsigned int splitType = 0) -> shared_ptr<BVH>;
auto top_down_sah(vector<shared_ptr<Object>> &objects, double parent_cost) -> shared_ptr<BVH>;

#endif
