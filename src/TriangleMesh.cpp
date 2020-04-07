
#include <TriangleMesh.h>

#include "TriangleMesh.h"
#include "Triangle.h"

auto TriangleMesh::intersect(const Ray &ray, double t_min, double &t_max, Vector3d &n, rgb &fr) const -> bool {
    bool did_intersect = false;
    for (const shared_ptr<Triangle> &triangle : triangles) {
        if (triangle->intersect(ray, t_min, t_max, n, fr)) {
            did_intersect = true;
        }
    }
    return did_intersect;
}

auto TriangleMesh::v_min() const -> Vector3d {
    return Eigen::Vector3d();
}

auto TriangleMesh::v_max() const -> Vector3d {
    return Eigen::Vector3d();
}

auto TriangleMesh::center() const -> Vector3d {
    return Eigen::Vector3d();
}
