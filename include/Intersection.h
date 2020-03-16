#ifndef CGPROJECT_INTERSECTION_H
#define CGPROJECT_INTERSECTION_H

#include "Object.h"
#include <vector>
#include <Ray.h>

using std::vector;
using std::shared_ptr;
using Eigen::Vector3d;

struct Intersection {
    double t; // parametric distance of ray
    Vector3d n; // normal vector
    shared_ptr<Object> object; // object intersected
    Ray ray;
};

auto find_nearest_intersection(const vector<shared_ptr<Object>> &objects, const Ray &ray, double offset,
                               Intersection &intersection) -> bool;

auto find_nearest_intersection(const Ray &ray, double &t, Vector3d &n, shared_ptr<Object> &hit_object,
                               const vector<shared_ptr<Object>> &objects) -> bool;

auto find_nearest_intersection(const vector<shared_ptr<Object>> &objects, const Ray &ray,
                               double t_min, double &t_max, Vector3d &n) -> bool;

auto find_intersection(const vector<shared_ptr<Object>> &objects, const Ray &ray, double t_max) -> bool;

#endif //CGPROJECT_INTERSECTION_H
