#include <iostream>
#include <PointLight.h>
#include "lambertian_reflection.h"
#include "Intersection.h"

void compute_reflected_light(rgb &diffuse_light, rgb &specular_light, vector<shared_ptr<Light>> &lights,
                             vector<shared_ptr<Object>> &objects, Intersection &intersection) {
    const Vector3d n = intersection.n;
    const Vector3d x = intersection.ray.eye + intersection.t * intersection.ray.direction;
    rgb kd = intersection.object->material->kd;
    for (shared_ptr<Light> &light : lights) {
        diffuse_light += kd * light->Le(n, x, objects);
    }
}
