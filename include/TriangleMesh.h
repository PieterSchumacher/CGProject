#ifndef TRIANGLE_MESH_H
#define TRIANGLE_MESH_H

#include "Object.h"
#include "../Eigen/Core"
#include <memory>
#include <vector>

using std::shared_ptr;
using std::vector;
using Eigen::Vector3d;

class Triangle;
class TriangleMesh : public Object {
  public:
    vector<shared_ptr<Object> > triangles;
    bool
    intersect(const Ray &ray, double t_min, double &t_max) const override;
};

#endif

