#ifndef OBJECT_H
#define OBJECT_H

#include "Material.h"
#include "Eigen"
#include <memory>

using std::shared_ptr;
using Eigen::Vector3d;
struct Ray;
class Object {
  public:
    shared_ptr<Material> material;
    virtual ~Object() {}
    virtual bool intersect(const Ray &ray, double t_min, double &t_max, Vector3d &n) const = 0;
};

#endif
