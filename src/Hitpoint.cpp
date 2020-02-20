#include <iostream>
#include "Hitpoint.h"

using std::cout;

bool find_nearest_hitpoint(const vector<shared_ptr<Object>> &objects, const Ray &ray, double offset, Hitpoint &hitpoint) {
    Vector3d n;
    bool intersect, did_intersect = false;
    double smallest_t_so_far = 1e6;
    for (const shared_ptr<Object> &object : objects) {
        intersect = object.get()->intersect(ray, offset, smallest_t_so_far, n);
        if (intersect) {
            did_intersect = true;
            hitpoint = {smallest_t_so_far, n, object, ray}; // what to do with object? if the original object gets deleted, will this too?
        }
    }
    return did_intersect;
}

