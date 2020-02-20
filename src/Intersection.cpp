#include <iostream>
#include "Intersection.h"

using std::cout;

bool find_nearest_intersection(const vector<shared_ptr<Object>> &objects, const Ray &ray, double offset,
                               Intersection &intersection) {
    Vector3d n;
    bool did_intersect = false;
    double smallest_t_so_far = 1e6;
    for (const shared_ptr<Object> &object : objects) {
        if (object.get()->intersect(ray, offset, smallest_t_so_far, n)) {
            did_intersect = true;
            intersection = {smallest_t_so_far, n, object, ray}; // what to do with object? if the original object gets deleted, will this too?
        }
    }
    return did_intersect;
}

