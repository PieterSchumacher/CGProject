#include "lambertian_reflection.h"
void compute_reflected_light(rgb &diffuse_light, rgb &specular_light, vector<shared_ptr<Light>> &lights, Vector3d x, Vector3d n) {
    for (shared_ptr<Light> &light : lights) {
        Vector3d l; double max_t;
        light->direction(x, l, max_t);
        double cosTheta = n.dot(l) / (n.norm() * l.norm());
        if (cosTheta > 1e-3) {
            diffuse_light += light->I * cosTheta;
        }
    }
}