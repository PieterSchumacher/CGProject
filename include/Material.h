#ifndef MATERIAL_H
#define MATERIAL_H
#include "../Eigen/Core"
#include "RGB.h"

struct Material {
    // Ambient, Diffuse, Specular
    rgb ka,kd,ks;
};

#endif
