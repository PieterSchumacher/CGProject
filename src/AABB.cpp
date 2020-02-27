#include "AABB.h"

bool AABB::intersect(const Ray &ray, double t_min, double &t_max, Vector3d &n) const {
    Vector3d T_min = (v_min - ray.eye).cwiseQuotient(ray.direction);
    Vector3d T_max = (v_max - ray.eye).cwiseQuotient(ray.direction);
    double t_1 = fmax(fmax(fmin(T_min(0), T_max(0)),
                           fmin(T_min(1), T_max(1))),
                           fmin(T_min(2), T_max(2)));
    if (t_min <= t_1 && t_1 < t_max) {
        double t_2 = fmin(fmin(fmax(T_min(0), T_max(0)),
                               fmax(T_min(1), T_max(1))),
                               fmax(T_min(2), T_max(2)));
        if (t_1 < t_2) {
            t_max = t_1;
            Vector3d diff = (v_min - (ray.eye + t_max*ray.direction)).cwiseAbs();
            n = diff(0) < 1e-12 ? Vector3d(-1,0,0)
              : diff(1) < 1e-12 ? Vector3d(0,-1,0)
              :                  Vector3d(0,0,-1);
            return true;
        }
    }
    return false;
}

