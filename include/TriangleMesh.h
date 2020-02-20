#ifndef TRIANGLE_MESH_H
#define TRIANGLE_MESH_H

#include "Object.h"
#include "../Eigen/Core"
#include <memory>
#include <vector>

using std::shared_ptr;
using std::vector;

class Triangle;
class TriangleMesh : public Object
{
  public:
    vector<shared_ptr<Object> > triangles;
    bool
    intersect(const Ray &ray, double min_t, double &smallest_t_so_far, Eigen::Vector3d &n) const;
};

#endif

