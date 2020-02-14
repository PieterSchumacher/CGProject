//
// Created by piete on 2/14/2020.
//

#ifndef CGPROJECT_RAY_H
#define CGPROJECT_RAY_H

#include "../../Eigen/src/Core/Matrix.h"

struct Ray {
    Eigen::Vector3d origin;
    Eigen::Vector3d direction;
};

#endif //CGPROJECT_RAY_H
