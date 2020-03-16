#ifndef CGPROJECT_SAMPLING_H
#define CGPROJECT_SAMPLING_H

#include <random>

using std::uniform_real_distribution;
using std::default_random_engine;

class Sampler {
private:
    uniform_real_distribution<double> unif;
    default_random_engine re;
public:
    Sampler() : unif(uniform_real_distribution<double>(0,1)) {}
    auto random(double a, double b) -> double;
    auto random() -> double;
};

#endif //CGPROJECT_SAMPLING_H
