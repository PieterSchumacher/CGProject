#include "Intersection.h"
#include <iostream>
bool find_nearest_intersection(const vector<shared_ptr<Object>> &objects, const Ray &ray, double offset,
                               Intersection &intersection) {
    Vector3d n;
    bool did_intersect = false;
    double smallest_t_so_far = 1e6;
    for (const shared_ptr<Object> &object : objects) {
        if (object->intersect(ray, offset, smallest_t_so_far, n)) {
            did_intersect = true;
            intersection = {smallest_t_so_far, n, object, ray}; // what to do with object? if the original object gets deleted, will this too?
        }
    }
    return did_intersect;
}

bool find_intersection(const vector<shared_ptr<Object>> &objects, const Ray &ray, double t_max) {
    Vector3d n; // not needed, maybe overload Object.intersect() without the normal? BUT then code duplication
    for (const shared_ptr<Object> &object : objects) {
        if (object->intersect(ray, -1e-12, t_max, n)) {
            return true;
        }
    }
    return false;
}
