#ifndef CAMERA_H
#define CAMERA_H

#include "Object.h"
#include "../Eigen/Core"

using Eigen::Vector3d;

struct Camera {
    Vector3d eye;
    Vector3d u,v,w;
    double d;
    double width, height;
};

#endif
