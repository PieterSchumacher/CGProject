#include "Intersection.h"
#include <iostream>

auto find_nearest_intersection(const Ray &ray, double &t, Vector3d &n, shared_ptr<Object> &hit_object, rgb &fr) -> bool {
    bool did_intersect = false;
    for (const shared_ptr<Object> &object : scene_objects) {
        if (object->intersect(ray, 1e-7, t, n, fr)) { // virtual function calls cause a lot of overhead?
            did_intersect = true;
            hit_object = object; // what to do with object? if the original object gets deleted, will this too?
        }
    }
    return did_intersect;
}

auto find_nearest_intersection(const vector<shared_ptr<Object>> &leaf_objects, const Ray &ray, double t_min, double &t_max,
                          Vector3d &n, rgb &fr) -> bool {
    bool did_intersect = false;
    for (const shared_ptr<Object> &object : leaf_objects) {
        if (object->intersect(ray, t_min, t_max, n, fr)) { // virtual function calls cause a lot of overhead?
            did_intersect = true;
        }
    }
    return did_intersect;
}

auto find_intersection(const Ray &ray, double t_max) -> bool {
    Vector3d n; // not needed, maybe overload Object.intersect() without the normal? BUT then code duplication
    rgb fr;
    for (const shared_ptr<Object> &object : scene_objects) {
        if (object->intersect(ray, 0, t_max, n, fr)) {
            return true;
        }
    }
    return false;
}
