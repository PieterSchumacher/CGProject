
#include <AreaLight.h>
#include "AreaLight.h"

rgb AreaLight::Le(const Vector3d &n, const Vector3d &x, const vector<shared_ptr<Object>> &objects) const {
    rgb radiance(0,0,0);
    for (unsigned char i = 0; i < N; ++i) {
//        sample->p = p + u*w*unif(re) + v*h*unif(re);
        radiance += sample->Le(n, x, objects);
    }
    return radiance / N;
}

AreaLight::AreaLight(Vector3d p1, Vector3d p2, Vector3d p3) : p(p1), u((p2-p1).normalized()), v((p3-p1).normalized()) {
    //    p2  --
    //      |    |
    //      |    |
    //    p1  --  p3
    h = (p2-p1).norm();
    w = (p3-p1).norm();
}
