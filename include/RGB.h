//
// Created by piete on 2/14/2020.
//

#ifndef CGPROJECT_RGB_H
#define CGPROJECT_RGB_H

#include "src/Core/Matrix.h"

struct rgb {
    double r,g,b,f;
    rgb(){r=0.0,g=0.0,b=0.0,f=0.0;};
    rgb(double r_, double g_, double b_) : r(r_), g(g_), b(b_), f(1.0) {}
    rgb(double r_, double g_, double b_, double f_) : r(r_), g(g_), b(b_), f(f_) {}

    rgb operator+(rgb c) {
        r += c.r, g += c.g, b += c.b;
        return *this;
    }

    rgb& operator+=(const rgb &c) {
        r += c.r, g += c.g, b += c.b;
        return *this;
    }

    rgb operator*(rgb c) {
        r *= c.r, g *= c.g, b *= c.b;
        return *this;
    }

    rgb operator*(double d) {
        r *= d, g *= d, b *= d;
        return *this;
    }

    rgb operator/(rgb c) {
        r /= c.r, g /= c.g, b /= c.b;
        return *this;
    }
};

#endif //CGPROJECT_RGB_H
