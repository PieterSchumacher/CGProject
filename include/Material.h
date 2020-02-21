#ifndef MATERIAL_H
#define MATERIAL_H
#include "RGB.h"

struct Material {
    // Ambient, Diffuse, Specular
    rgb ka,kd,ks;
};

#endif
