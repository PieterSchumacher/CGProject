#ifndef LIGHT_H
#define LIGHT_H

#include "RGB.h"
#include "Object.h"
#include <Intersection.h>

using std::shared_ptr;
using std::vector;
using Eigen::Vector3d;

class Light {
  public:
    double I;   // Intensity
    rgb c;      // Color
    Vector3d normal;
    static const unsigned char N = 9;
    static const unsigned char sample_rate = 3;
    virtual ~Light() = default;
    virtual auto wi(const Vector3d &x, const double du, const double dv) const -> Vector3d = 0;
    virtual auto pdf(const Vector3d &p) const -> double {return 1;}
    static auto V(const Vector3d &p, const Vector3d &p_prime) -> bool {
        Vector3d wo = p - p_prime;
        return !find_intersection({p_prime+wo*1e-11, wo.normalized()}, wo.norm()-1e-10);
    }
    auto G(const Vector3d &p, const Vector3d &p_prime, const Vector3d &n) const -> double {
        Vector3d wi = p_prime - p;
        return n.dot(wi.normalized()) * normal.dot(-wi.normalized()) / wi.squaredNorm();
    };
    // @precondition: n is a normalized vector
    auto Li(const Vector3d &p, const Vector3d &n) const -> rgb {
        // Stratified Monte Carlo sampling
        double L = 0;                       // Wavelength independent radiance value
        rgb Le = c * I * 2 * 3.1415 / (N*pow(pdf(p), 2));   // Emittance of the light source
        Vector3d p_prime;                   // Sample point of the light source
        for (unsigned k=0; k < sample_rate; ++k) {
            for (unsigned l = 0; l < sample_rate; ++l) {
                p_prime = wi(p,k,l) + p;
                L += V(p, p_prime) ? G(p, p_prime, n) : 0;
            }
        }
        return Le * L / N;
    }
};
#endif
