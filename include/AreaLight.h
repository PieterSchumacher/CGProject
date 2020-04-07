#ifndef CGPROJECT_AREALIGHT_H
#define CGPROJECT_AREALIGHT_H

#include "Light.h"
#include "sampling.h"
#include <PointLight.h>
#include <random>

using Eigen::Vector3d;
using std::default_random_engine;
using std::uniform_real_distribution;
using std::move;
using std::unique_ptr;
class AreaLight : public Light, public Object {
private:
    // lowerleft most point and local 2D orthonormal basis vectors
    Vector3d p, u, v;
public:
    // 3 points define a rectangle
    AreaLight(const Vector3d& p1, const Vector3d& p2, const Vector3d& p3);

    auto wi(const Vector3d &x, const double du, const double dv) const -> Vector3d override;

    auto pdf(const Vector3d &p_prime) const -> double override {
        return 1 / (u.norm() * v.norm());
    }

    auto Le(const Vector3d &x, const Vector3d &wo) const -> rgb override;

    auto intersect(const Ray &ray, double t_min, double &t_max, Vector3d &n, rgb &fr) const -> bool override;
    auto v_min() const -> Vector3d override;
    auto v_max() const -> Vector3d override;
    auto center() const -> Vector3d override;
};

#endif //CGPROJECT_AREALIGHT_H
