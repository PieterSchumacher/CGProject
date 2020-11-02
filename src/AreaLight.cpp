
#include <AreaLight.h>
#include <iostream>
#include <memory>

auto AreaLight::wi(const Vector3d &x, const double du, const double dv) const -> Vector3d {
    return (p + (u*(du+sampler->random()) + v*(dv+sampler->random())) / sqrt(N)) - x;
}

AreaLight::AreaLight(const Vector3d& p1, const Vector3d& p2, const Vector3d& p3)
                        : p(p1), u(p3-p1), v(p2-p1) {
    //    p2  --                  --
    //      |    |      == >    |    |
    //      |    |      == >  v |    |
    //    p1  --  p3            p --
    //                            u
    this->c = rgb(1,1,1);
    this->I = 1;
    this->normal = u.cross(v).normalized();
    std::cout << normal << "\n";
}

auto AreaLight::intersect(const Ray &ray, double t_min, double &t_max, Vector3d &n, rgb &fr) const -> bool {
    double t = (p - ray.x).dot(normal) / ray.wo.dot(normal);
    if (t <= t_min || t_max < t) {
        return false;
    }
    Vector3d d = ray.x + t * ray.wo - p;
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
    fr = material->kd;
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
//    std::cout << "pdf arealight: " << pdf(x) << "\n";

    return c * I * material->kd / pdf(x);
}
