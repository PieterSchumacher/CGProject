#include "Object.h"
#include "Ray.h"
#include "Camera.h"
#include "Light.h"
#include "Ray.h"
#include "RGB.h"
#include <iostream>
#include <vector>
#include <memory>
#include <Sphere.h>
#include <write_ppm.h>
#include "Eigen/Dense"

using Eigen::Vector3d;
using std::max;
using std::min;
using std::vector;
using std::shared_ptr;

int main(int argc, char * argv[]) {
    Camera camera = {Vector3d(0,0,0), Vector3d(0,0,1), Vector3d(0,-1,0), Vector3d(0,0,-1), 0.5, 640, 360};

    Sphere s;

    vector<shared_ptr<Object>> objects;
    vector<shared_ptr<Light>> lights;
    // Initialize scene and camera
    shared_ptr<Sphere> sphere(new Sphere());
    sphere->center = Vector3d(0,3,0);
    sphere->radius = 1.0;
    objects.push_back(sphere);

    unsigned int width = 640;
    unsigned int height = 360;
    vector<unsigned char> rgb_image(3*width*height);
    // For each pixel (i,j)
    #pragma omp parallel for
    for (unsigned i=0; i < height; ++i) {
        for (unsigned j=0; j < width; ++j) {
            // Set background color
            rgb background_color = rgb(0,0,0);

            // Compute viewing ray  -- in : camera,i,j,width,height,ray --
            Ray ray;

            // Shoot ray and collect color -- in : ray,1.0,objects,lights,0,rgb --
            rgb color = rgb(255.0-i, 255.0-i, 255.0-i);
            // Write double precision color into image
            auto clamp = [](double s){return max(min(s,1.0),0.0);};
            rgb_image[0+3*(j+width*i)] = 255.0*clamp(color.r/255.0);
            rgb_image[1+3*(j+width*i)] = 255.0*clamp(color.g/255.0);
            rgb_image[2+3*(j+width*i)] = 255.0*clamp(color.b/255.0);
        }
    }

    // write to file -- in : str filename, rgb_image, width, height, 3
    std::string filename = "CGDemo";
    write_ppm(filename, rgb_image, width, height);
}
