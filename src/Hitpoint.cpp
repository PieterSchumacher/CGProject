#include <iostream>
#include "Hitpoint.h"

using std::cout;

bool find_nearest_hitpoint(const vector<shared_ptr<Object>> &objects, const Ray &ray, double offset, Hitpoint &hitpoint) {
    double t = 0.0; Vector3d n; bool intersect, did_intersect = false; double smallest_t_so_far = 1e8;
    for (const shared_ptr<Object> &object : objects) {
        intersect = object.get()->intersect(ray, offset, t, n);
        if (intersect && t < smallest_t_so_far) {
            did_intersect = true;
            smallest_t_so_far = t;
            hitpoint = {smallest_t_so_far, n, object, ray}; // what to do with object? if the original object gets deleted, will this too?
        }
    }

    return did_intersect;
}

