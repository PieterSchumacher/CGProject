#ifndef CGPROJECT_AABB_H
#define CGPROJECT_AABB_H
#include "Eigen"
#include "Object.h"
#include "Ray.h"
#include <cmath>

using Eigen::Vector3d;
using std::fmin;
using std::fmax;
using std::move;

class AABB : public Object {
public:
    Vector3d vmin, vmax;
    AABB() {};
    AABB(Vector3d v_min, Vector3d v_max);
    bool intersect(const Ray &ray, double t_min, double t_max) const;
    bool intersect(const Ray &ray, double t_min, double &t_max, Vector3d &n) const override;
    Vector3d v_min() const override;
    Vector3d v_max() const override;
    Vector3d center() const override;
};


#endif //CGPROJECT_AABB_H
