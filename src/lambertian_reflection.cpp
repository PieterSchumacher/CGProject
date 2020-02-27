#include <iostream>
#include "lambertian_reflection.h"
#include "Intersection.h"
void compute_reflected_light(rgb &diffuse_light, rgb &specular_light, vector<shared_ptr<Light>> &lights,
                             vector<shared_ptr<Object>> &objects, Intersection &intersection) {
    const Vector3d n = intersection.n;
    const Vector3d x = intersection.ray.eye + intersection.t * intersection.ray.direction;
    rgb kd = intersection.object->material->kd;
    for (shared_ptr<Light> &light : lights) {
        Vector3d l;
        double max_t;
        light->direction(x, l, max_t);
        double cosTheta = n.dot(l) / l.norm();

        if (cosTheta > 1e-12 && !find_intersection(objects, {l + x, -l.normalized()}, l.norm() - 1e-12) ) {
            diffuse_light += kd * light->I * cosTheta;
        }
    }
}