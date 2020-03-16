//
// Created by piete on 3/13/2020.
//

#include <sampling.h>

double Sampler::random(double a, double b) {
    return a * (unif(re) - a / (b - a)); // double check, this is interpolation
}
double Sampler::random() {
    return unif(re); // double check, this is interpolation
}

