#ifndef MATERIAL_H
#define MATERIAL_H
#include "RGB.h"
#include <memory>
#include <vector>
#include <iostream>

using std::shared_ptr;
using std::vector;

extern vector<shared_ptr<rgb>> texture;

struct Material {
    // Ambient, Diffuse, Specular
    rgb ka=rgb(0,0,0),kd=rgb(0,0,0),ks=rgb(0,0,0);
    rgb texture_colour(const double u, const double v) {
//        return *texture[floor(u*c + c*floor((1-v)*r))] / 255;
        return kd;
    }
};

#endif
