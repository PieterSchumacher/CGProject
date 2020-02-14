//
// Created by piete on 2/14/2020.
//

#ifndef CGPROJECT_CAMERA_H
#define CGPROJECT_CAMERA_H

#include "../../Eigen/src/Core/Matrix.h"

struct Camera {
    Eigen::Vector3d e;
    Eigen::Vector3d u,v,w;
    double d;
    double width, height;
};

#endif //CGPROJECT_CAMERA_H
