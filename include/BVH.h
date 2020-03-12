#include <utility>

#ifndef CGPROJECT_BVH_H
#define CGPROJECT_BVH_H

#include <memory>
#include "Eigen"
#include "Object.h"
#include "AABB.h"
#include "Intersection.h"
#include "Triangle.h"

using std::shared_ptr;
using std::size_t;
using std::tuple;
using std::fmod;
using std::move;
using std::make_shared;
using Eigen::Vector3d;
struct Ray;

// https://en.wikipedia.org/wiki/Composite_pattern
class BVH : public Object {
public:
    AABB box;
    virtual ~BVH() {};
    Vector3d v_min() const override;
    Vector3d v_max() const override;
    Vector3d center() const override;
    virtual void bounding_boxes(vector<shared_ptr<Object>> &objects) const = 0;
};

class BVHNode : public BVH {
public:
    BVHNode(const shared_ptr<BVH> &right, const shared_ptr<BVH> &left) : right(move(right)), left(move(left)) {};
    shared_ptr<BVH> right;
    shared_ptr<BVH> left;
    bool intersect(const Ray &ray, double t_min, double &t_max, Vector3d &n) const override;
    void bounding_boxes(vector<shared_ptr<Object>> &objects) const override;
};

class BVHLeaf : public BVH {
public:
    explicit BVHLeaf(const vector<shared_ptr<Object>> objects) : objects(move(objects)) {};
    vector<shared_ptr<Object>> objects;
    bool intersect(const Ray &ray, double t_min, double &t_max, Vector3d &n) const override;
    void bounding_boxes(vector<shared_ptr<Object>> &objects) const override;
};

shared_ptr<BVH> top_down(vector<shared_ptr<Object>> &objects, const unsigned int splitType, Vector3d v_min = Vector3d(1e6, 1e6, 1e6), Vector3d v_max = Vector3d(-1e6, -1e6, -1e6));
#endif //CGPROJECT_BVH_H
