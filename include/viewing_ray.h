#ifndef VIEWING_RAY_H
#define VIEWING_RAY_H

#include "Ray.h"
#include "Camera.h"

void viewing_ray(
  const Camera & camera,
  const int i,
  const int j,
  const int width,
  const int height,
  Ray & ray);
#endif
