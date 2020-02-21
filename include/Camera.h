#ifndef CAMERA_H
#define CAMERA_H

#include "Object.h"
#include <Ray.h>

using Eigen::Vector3d;

struct Camera {
    Vector3d eye;
    Vector3d look_at;
    Vector3d u,v,w;
    double d;
    double h_res, v_res;
    double s;

    Camera(Vector3d e, Vector3d l, double plane_offset, double hres, double vres, double pixel_size);

    void shoot_ray(double c, double r, Ray &ray);

};

#endif
