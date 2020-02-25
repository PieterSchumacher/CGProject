#include "Camera.h"
#include <utility>
#include <iostream>

using std::cout;
Camera::Camera(Vector3d e, Vector3d l, double plane_offset, double hres, double vres, double pixel_size) {
    eye = std::move(e); look_at = std::move(l); d = plane_offset; h_res = hres; v_res = vres; s = pixel_size;
    w = (eye - look_at).normalized();
    u = Vector3d(0,0, 1).cross(w).normalized();
    v = u.cross(w);
    cout << "w: " << w << "\n";
    cout << "u: " << u << "\n";
    cout << "v: " << v << "\n";
}
void Camera::shoot_ray(double c, double r, Ray &ray) {
    double x = s*(c - (h_res/2.0) + 0.5);
    double y = s*(r - (v_res/2.0) + 0.5);
    ray = {eye, (x*u + y*v - d*w).normalized()};

}

