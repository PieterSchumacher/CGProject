#ifndef OBJECT_H
#define OBJECT_H

#include "Material.h"
#include "Eigen"
#include <memory>

using std::shared_ptr;
using std::vector;
using Eigen::Vector3d;
struct Ray;
class Object {
  public:
    shared_ptr<Material> material;
    virtual ~Object() = default;
    virtual auto intersect(const Ray &ray, double t_min, double &t_max, Vector3d &n) const -> bool = 0;

    virtual auto Le(const Vector3d &x, const Vector3d &wo) const -> rgb {return {0,0,0};};
    virtual auto v_min() const -> Vector3d = 0;
    virtual auto v_max() const -> Vector3d = 0;
    virtual auto center() const -> Vector3d = 0;
};

#endif
