#ifndef CGPROJECT_LAMBERTIAN_REFLECTION_H
#define CGPROJECT_LAMBERTIAN_REFLECTION_H
#include "RGB.h"
#include "Light.h"
#include <memory>
#include <vector>
#include <cmath>

using std::vector;
using std::shared_ptr;
using Eigen::Vector3d;
void compute_reflected_light(rgb &diffuse_light, rgb &specular_light, vector<shared_ptr<Light>> &lights, Vector3d x, Vector3d n);
#endif
