
#include <AreaLight.h>
#include <iostream>
#include <memory>

auto AreaLight::wi(const Vector3d &x) const -> Vector3d {
    return (p + u*sampler->random() + v*sampler->random()) - x;
}

AreaLight::AreaLight(const Vector3d& p1, const Vector3d& p2, const Vector3d& p3, shared_ptr<Sampler> sampler)
                        : p(p1), u(p3-p1), v(p2-p1), normal(u.cross(v).normalized()), sampler(move(sampler)) {
    //    p2  --                  --
    //      |    |      == >    |    |
    //      |    |      == >  v |    |
    //    p1  --  p3            p --
    //                            u
    this->I = rgb(253,233,153)*0.7;
}

auto AreaLight::intersect(const Ray &ray, double t_min, double &t_max, Vector3d &n) const -> bool {
    double t = (p - ray.eye).dot(normal) / ray.direction.dot(normal);
    if (t < t_min || t_max < t) {
        return false;
    }
    Vector3d d = ray.eye + t * ray.direction - p;
    double t1 = d.dot(u);
    if (t1 < 0 || u.squaredNorm() < t1) {
        return false;
    }
    double t2 = d.dot(v);
    if (t2 < 0 || v.squaredNorm() < t2) {
        return false;
    }
    t_max = t;
    n = normal;
    return true;
}

auto AreaLight::v_min() const -> Vector3d {
    return p;
}

auto AreaLight::v_max() const -> Vector3d {
    return p + u + v;
}

auto AreaLight::center() const -> Vector3d {
    return p + (u + v)/2;
}

auto AreaLight::Le(const Vector3d &x, const Vector3d &wo) const -> rgb {
    rgb I = this->I;
    return I;
}

auto AreaLight::samples(const Vector3d &x) const -> vector<Vector3d> {
    vector<Vector3d> samples;
    for (unsigned char i = 0; i < N; ++i) {
        samples.push_back(wi(x));
    }
    return samples;
}
