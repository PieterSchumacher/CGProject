#include <iostream>
#include "lambertian_reflection.h"
#include "Intersection.h"
void compute_reflected_light(rgb &diffuse_light, rgb &specular_light, vector<shared_ptr<Light>> &lights,
                             vector<shared_ptr<Object>> &objects, const Vector3d &n, const Vector3d &x) {
    for (shared_ptr<Light> &light : lights) {
        Vector3d l;
        double max_t;
        light->direction(x, l, max_t);
        double cosTheta = n.dot(l) / (n.norm() * l.norm());
        if (cosTheta > -1e-6 && !find_intersection(objects, {l + x, -l.normalized()}, l.norm()-1e-6) ) {
            diffuse_light += light->I * cosTheta;
        }
    }
}