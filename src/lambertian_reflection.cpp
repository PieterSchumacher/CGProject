#include <iostream>
#include <Light.h>
#include "lambertian_reflection.h"
#include "Intersection.h"

auto Lo(Ray &ray,
        vector<shared_ptr<Light>> &lights,
        vector<shared_ptr<Object>> &objects) -> rgb {
    // Outgoing radiance
    rgb Lo              = rgb(0,0,0);

    // Compute nearest intersection
    double t            = 1e6;
    Vector3d n;
    shared_ptr<Object> object;
    bool did_intersect  = find_nearest_intersection(ray, t, n, object, objects);

    // Compute outgoing radiance of nearest intersection
    if (did_intersect) {
        const Vector3d wo   = - t * ray.direction;
        const Vector3d x    = ray.eye - wo;
        const unsigned N    = Light::N * lights.size();
        rgb Li              = rgb(0,0,0);
        for (shared_ptr<Light> &light : lights) {
            for (const Vector3d &wi : light->samples(x)) {
                Li += light->Li(x, wi, objects) * n.dot(wi.normalized());
            }
        }
        // https://en.wikipedia.org/wiki/Rendering_equation
        Lo += object->Le(x, wo) + (object->material->kd * Li / N);
    }
    return Lo;
}

auto Li(Vector3d &x, Vector3d &wi,
        vector<shared_ptr<Light>> &lights,
        vector<shared_ptr<Object>> &objects) -> rgb {

}
