//
// Created by piete on 2/14/2020.
//

#ifndef CGPROJECT_RGB_H
#define CGPROJECT_RGB_H
#include <cmath>
struct rgb {
    double r,g,b,f;
    rgb(){r=0.0,g=0.0,b=0.0,f=0.0;};
    rgb(double r_, double g_, double b_) : r(r_), g(g_), b(b_), f(1.0) {}
    rgb(double r_, double g_, double b_, double f_) : r(r_), g(g_), b(b_), f(f_) {}

    rgb operator+(rgb c) {
        return {r+c.r, g+c.g, b+c.b};
    }

    rgb& operator+=(const rgb &c) {
        r += c.r, g += c.g, b += c.b;
        return *this;
    }

    rgb operator*(rgb c) {
        return {r*c.r, g*c.g, b*c.b};
    }

    rgb operator*(double d) {
        return {r*d, g*d, b*d};
    }

    rgb operator/(rgb c) {
        return {r/c.r, g/c.g, b/c.b};
    }

    rgb operator/(double d) {
        return {r/d, g/d, b/d};
    }

    rgb operator^(double e) {
        return {pow(r, e), pow(g, e), pow(b, e)};
    }
};

#endif //CGPROJECT_RGB_H
