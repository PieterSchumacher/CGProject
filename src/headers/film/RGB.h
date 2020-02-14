//
// Created by piete on 2/14/2020.
//

#ifndef CGPROJECT_RGB_H
#define CGPROJECT_RGB_H

#include "../../../Eigen/src/Core/Matrix.h"

struct rgb {
    double r,g,b,f;

    rgb(double r_, double g_, double b_) : r(r_), g(g_), b(b_), f(1.0) {}
    rgb(double r_, double g_, double b_, double f_) : r(r_), g(g_), b(b_), f(f_) {}

    rgb operator+(rgb c) {
        r += c.r, g += c.g, b += c.b;
        return *this;
    }

    rgb operator*(rgb c) {
        r *= c.r, g *= c.g, b *= c.b;
        return *this;
    }

    rgb operator/(rgb c) {
        r /= c.r, g /= c.g, b /= c.b;
        return *this;
    }
};

#endif //CGPROJECT_RGB_H
