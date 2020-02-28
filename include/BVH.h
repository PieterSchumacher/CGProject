#ifndef CGPROJECT_BVH_H
#define CGPROJECT_BVH_H

#include <memory>
#include <src/Core/Matrix.h>
#include "Object.h"
#include "TriangleMesh.h"
#include "AABB.h"
#include "Triangle.h"

using std::shared_ptr;
using Eigen::Vector3d;
struct Ray;

// https://en.wikipedia.org/wiki/Composite_pattern
class BVH : public Object {
public:
    AABB box;
    virtual ~BVH() {}
    virtual bool intersect(const Ray &ray, double t_min, double &t_max, Vector3d &n) const override;
};

class BVHNode : public BVH {
public:
    BVH right;
    BVH left;
    bool intersect(const Ray &ray, double t_min, double &t_max, Vector3d &n) const override;
};

class BVHLeaf : public BVH {
public:
    TriangleMesh triangles;
    bool intersect(const Ray &ray, double t_min, double &t_max, Vector3d &n) const override;
};

#endif //CGPROJECT_BVH_H
