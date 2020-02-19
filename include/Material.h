#ifndef MATERIAL_H
#define MATERIAL_H
#include "../Eigen/Core"
#include "RGB.h"

// Blinn-Phong Approximate Shading Material Parameters
struct Material {
    // Ambient, Diffuse, Specular, Mirror Color
    rgb ka,kd,ks,km;
    // Phong exponent
    double phong_exponent{};
};
#endif
