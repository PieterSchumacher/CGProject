#include <iostream>
#include "PointLight.h"

void PointLight::direction(
  const Vector3d & q, Vector3d & d, double & max_t) const {
//    std::cout << "q: " << q << "\n";
//    std::cout << "p: " << p << "\n";
//    std::cout << "d: " << d << "\n";
    d = p - q;
}
