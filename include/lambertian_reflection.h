#ifndef CGPROJECT_LAMBERTIAN_REFLECTION_H
#define CGPROJECT_LAMBERTIAN_REFLECTION_H
#include "RGB.h"
#include "Light.h"
#include "Object.h"
#include "Ray.h"
#include "Intersection.h"
#include <memory>
#include <vector>
#include <cmath>

using std::vector;
using std::shared_ptr;
using Eigen::Vector3d;

auto Lo(const Ray &ray, unsigned depth=0, bool not_double_path=true) -> rgb;

#endif
