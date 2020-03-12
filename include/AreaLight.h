#ifndef CGPROJECT_AREALIGHT_H
#define CGPROJECT_AREALIGHT_H

#include "Light.h"
#include <PointLight.h>
#include <random>

using Eigen::Vector3d;
using std::default_random_engine;
using std::uniform_real_distribution;

class AreaLight : public Light {
private:
    unsigned char N = 3;
public:
    uniform_real_distribution<double> unif;
    default_random_engine re;
    shared_ptr<PointLight> sample;
    // lowerleft most point and local 2D orthonormal basis vectors
    Vector3d p, u, v;
    // width && height
    double w, h;
    // 2 points define a rectangle
    AreaLight(Vector3d p1, Vector3d p2, Vector3d p3);
    rgb Le(const Vector3d &n, const Vector3d &x, const vector<shared_ptr<Object>> &objects) const override;
};

#endif //CGPROJECT_AREALIGHT_H
