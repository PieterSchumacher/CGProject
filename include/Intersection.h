#ifndef CGPROJECT_INTERSECTION_H
#define CGPROJECT_INTERSECTION_H

#include "Object.h"
#include <Ray.h>
#include "sampling.h"

using std::vector;
using std::shared_ptr;
using Eigen::Vector3d;

class Light;

extern vector<shared_ptr<Object>> scene_objects;
extern vector<shared_ptr<Light>> lights;
extern shared_ptr<Sampler> sampler;
extern double nb_intersections;

auto find_nearest_intersection(const Ray &ray, double &t, Vector3d &n, shared_ptr<Object> &hit_object, rgb &fr) -> bool;

auto find_nearest_intersection(const vector<shared_ptr<Object>> &leaf_objects, const Ray &ray, double t_min, double &t_max,
                          Vector3d &n, rgb &fr) -> bool;

auto find_intersection(const Ray &ray, double t_max) -> bool;

#endif //CGPROJECT_INTERSECTION_H
