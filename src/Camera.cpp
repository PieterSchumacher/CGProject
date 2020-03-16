#include "Camera.h"
#include <utility>
#include <iostream>

using std::cout;
Camera::Camera(Vector3d e, Vector3d l, double plane_offset, double hres, double vres, double pixel_size) {
    eye = std::move(e); look_at = std::move(l); d = plane_offset; h_res = hres; v_res = vres; s = pixel_size;
    w = (eye - look_at).normalized();
    u = Vector3d(0,1,0).cross(w).normalized();
    v = w.cross(u);
}
void Camera::shoot_ray(double c, double r, Ray &ray) {
    double x = s*(c - (h_res/2.0));
    double y = s*(r - (v_res/2.0));
    ray = {eye, (x*u + y*v - d*w).normalized()};

}

