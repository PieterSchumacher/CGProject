#include "TriangleMesh.h"
#include "Triangle.h"

bool TriangleMesh::intersect(const Ray &ray, double t_min, double &t_max, Vector3d &n) const {
    bool did_intersect = false;
    for (const shared_ptr<Triangle> &triangle : triangles) {
        if (triangle->intersect(ray, t_min, t_max, n)) {
            did_intersect = true;
        }
    }
    return did_intersect;
}
