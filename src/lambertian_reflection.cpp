#include <iostream>
#include <AreaLight.h>
#include "lambertian_reflection.h"

auto clamp = [](double s){return s < 1.0/3.0 ? 0.0 : s;};

auto Lo(const Ray &ray, unsigned depth, bool double_path) -> rgb {
    // Outgoing radiance
    rgb L = rgb(0, 0, 0);

    // Compute nearest intersection and add it's outgoing radiance value
    double   t = 1e6;
    Vector3d n;
    shared_ptr<Object> object;
    rgb fr, fs;
    //
    if (find_nearest_intersection(ray, t, n, object, fr) && (!double_path || dynamic_cast<AreaLight*>(object.get()) == nullptr)) {
        rgb Li              = rgb(0,0,0);
        rgb Ls              = rgb(0,0,0);
        const Vector3d wo   = - t * ray.wo;
        const Vector3d x    = ray.x - wo;
        fs = object->material->ks;
        // Alpha
        const double f  = clamp(1.14*sqrt(tanh(1 - (depth/15.0))));
        const double ad = f*(fr.r+fr.g+fr.b)/3;
        const double as = f*(fs.r+fs.g+fs.b)/3;
        for (shared_ptr<Light> &light : lights) {
            Li += light->Li(x, n);
        }
        Vector3d wi, r;
        // Russian Roulette
        if (sampler->random() < ad) {
            // Shoot a new ray somewhere on the unit hemisphere defined by the hit normal. Add the outgoing radiance
            // from that direction to the total incoming radiance of the hit point
            wi = sampler->sample(n);
            Li +=  Lo({x, wi}, depth+1, true) * n.dot(wi) / ad;
        }
        if (sampler->random() < as) {
            r = (-wo + 2 * (n.dot(wo)) * n).normalized();
            Ls += Lo({x, r}, depth+1) * n.dot(r) / as;
        }
        // https://en.wikipedia.org/wiki/Rendering_equation
        L += object->Le(x, wo) + fr*Li + fs*Ls;
    }
    return L;
}
