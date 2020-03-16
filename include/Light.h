#ifndef LIGHT_H
#define LIGHT_H
#include "Eigen"
#include "RGB.h"
#include "Object.h"
#include <Intersection.h>

using std::shared_ptr;
using std::vector;
using Eigen::Vector3d;

class Light {
  public:
    // Color (intensities)
    rgb I{};
    static const unsigned char N = 4;
    virtual ~Light() = default;
    virtual auto wi(const Vector3d &x) const -> Vector3d = 0;
    virtual auto samples(const Vector3d &x) const -> vector<Vector3d> = 0;
    auto Li(const Vector3d &x, const Vector3d &wi, const vector<shared_ptr<Object>> &objects) const -> rgb {
        return !find_intersection(objects, {x, wi.normalized()}, wi.norm()-1e-9) ? I : rgb(0,0,0);
    };
};
#endif
