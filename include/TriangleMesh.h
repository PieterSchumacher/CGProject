#ifndef TRIANGLE_MESH_H
#define TRIANGLE_MESH_H

#include "Object.h"
#include "Eigen"
#include <memory>
#include <numeric>
#include <tuple>
#include <vector>

using std::shared_ptr;
using std::tuple;
using std::get;
using std::accumulate;
using std::vector;
using Eigen::Vector3d;

class Triangle;
class TriangleMesh : public Object {
  public:
    vector<shared_ptr<Triangle>> triangles;
    TriangleMesh(vector<shared_ptr<Triangle>> &triangles) : triangles(move(triangles)){};
    bool intersect(const Ray &ray, double t_min, double &t_max, Vector3d &n) const override;
    Vector3d v_min() const override;
    Vector3d v_max() const override;
    Vector3d center() const override;
};

#endif

