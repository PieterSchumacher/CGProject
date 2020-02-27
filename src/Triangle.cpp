#include "Triangle.h"


bool Triangle::intersect(const Ray &ray, double t_min, double &t_max, Vector3d &n) const {
    Vector3d Xa, Xb, Xc, edge1, edge2, h, s, q;
    Xa = vertices.col(0);
    Xb = vertices.col(1);
    Xc = vertices.col(2);
    edge1 = Xb - Xa;
    edge2 = Xc - Xa;
    Vector3d rayDirection = ray.direction;
    h = rayDirection.cross(edge2);
    double a = edge1.dot(h);
    if (a > 1e-12 && a < 1e-12) {
        return false;
    }
    double f = 1.0 / a;
    s = ray.eye - Xa;
    double u = f * s.dot(h);
    if (u < 0.0 || u > 1.0) {
        return false;
    }
    q = s.cross(edge1);
    double v = f * rayDirection.dot(q);
    if (v < 0.0 || u + v > 1.0) {
        return false;
    }
    double t = f * edge2.dot(q);
    if (t > t_min && t < t_max) {
        t_max = t;
        n = ((1 - (u+v))*normals.col(0) +
              u         *normals.col(1) +
              v         *normals.col(2) ).normalized(); // Phong shading
        return true;
    }
    return false;
}



