#include "Intersection.h"

bool find_nearest_intersection(const vector<shared_ptr<Object>> &objects, const Ray &ray, double offset,
                               Intersection &intersection) {
    Vector3d n;
    bool did_intersect = false;
    double smallest_t_so_far = 1e6;
    for (const shared_ptr<Object> &object : objects) {
        if (object->intersect(ray, offset, smallest_t_so_far)) {
            did_intersect = true;
            object->get_normal((ray.eye + smallest_t_so_far * ray.direction), n);
            intersection = {smallest_t_so_far, n, object, ray}; // what to do with object? if the original object gets deleted, will this too?
        }
    }
    return did_intersect;
}

bool find_intersection(const vector<shared_ptr<Object>> &objects, const Ray &ray, double &t_max) {
    for (const shared_ptr<Object> &object : objects) {
        if (object->intersect(ray, -1e-6, t_max)) {
            return true;
        }
    }
    return false;
}


