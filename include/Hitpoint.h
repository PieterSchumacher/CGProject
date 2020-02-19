#ifndef CGPROJECT_HITPOINT_H
#define CGPROJECT_HITPOINT_H

#include "Object.h"
#include <vector>
#include <Ray.h>

using std::vector;
using std::shared_ptr;
using Eigen::Vector3d;

struct Hitpoint {
    double t; // parametric distance of ray
    Vector3d n; // normal vector
    shared_ptr<Object> object; // object intersected
    Ray ray;
};

bool find_nearest_hitpoint(const vector<shared_ptr<Object>> &objects, const Ray &ray, double offset, Hitpoint &hitpoint);

#endif //CGPROJECT_HITPOINT_H
