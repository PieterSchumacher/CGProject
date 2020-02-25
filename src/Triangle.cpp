#include "Triangle.h"


bool Triangle::intersect(const Ray &ray, double t_min, double &t_max, Vector3d &n) const {
    Matrix3d A;
    Vector3d b;
    A << vertices.col(0) - vertices.col(1), // Xa - Xb
         vertices.col(0) - vertices.col(2), // Xa - Xc
         ray.direction;                     // Xd
    b << vertices.col(0) - ray.eye;         // Xa - Xe
    Vector3d x = A.lu().solve(b);  // does the compiler replace vertices.col(0) with a variable?
    double a = x(0) + x(1);
    if (0 < x(0) && x(0) < 1 &&
        0 < x(1) && x(1) < 1 &&
        0 < a    && a    < 1 &&
        0 < x(2) && x(2) < t_max) { // how to speed up branch?
        t_max = x(2);
        n = ( a   *normals.col(0) +
              x(0)*normals.col(1) +
              x(1)*normals.col(2) ); // Phong shading
        return true;
    }
    return false; // VERY slow
}



