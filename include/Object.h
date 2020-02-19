#ifndef OBJECT_H
#define OBJECT_H

#include "Material.h"
#include "../Eigen/Core"
#include <memory>

using std::shared_ptr;

struct Ray;
class Object {
  public:
    shared_ptr<Material> material;
    virtual ~Object() {}
    virtual bool
    intersect(const Ray &ray, double min_t, double &t, Eigen::Vector3d &n) const = 0;
};

#endif
