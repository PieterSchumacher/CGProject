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
    virtual ~Light() {};
    virtual void direction(const Vector3d & q, Vector3d & d, double & max_t) const = 0;
    virtual rgb Le(const Vector3d &n, const Vector3d &x, const vector<shared_ptr<Object>> &objects) const = 0;
};
#endif
