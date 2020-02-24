#ifndef CGPROJECT_AABB_H
#define CGPROJECT_AABB_H
#include "Eigen"
#include "Object.h"
#include "Ray.h"
#include <cmath>

using Eigen::Vector3d;
using std::fmin;
using std::fmax;

class AABB : public Object {
public:
    Vector3d v_min;
    Vector3d v_max;
    bool intersect(const Ray &ray, double t_min, double &t_max, Vector3d &n) const override;
};


#endif //CGPROJECT_AABB_H
