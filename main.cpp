#include "src/headers/Shape.h"
#include "src/headers/Ray.h"
#include "src/headers/Camera.h"
#include "src/headers/LightSource.h"
#include "src/headers/Ray.h"
#include <iostream>
#include <vector>
#include <memory>
#include "Eigen/Dense"
#include "src/headers/film/RGB.h"
#include "src/headers/Camera.h"

using Eigen::Vector3d;
using std::max;
using std::min;
using std::vector;
using std::shared_ptr;

int main(int argc, char * argv[]) {
    Camera camera;
    vector<shared_ptr<Shape>> objects;
    vector<shared_ptr<LightSource>> lights;
    // Initialize scene and camera

    int width =  640;
    int height = 360;
    vector<unsigned char> rgb_image(3*width*height);
    // For each pixel (i,j)
    for(unsigned i=0; i<height; ++i) {
        for(unsigned j=0; j<width; ++j) {
            // Set background color
            rgb background_color = rgb(0, 0, 0);

            // Compute viewing ray  -- in : camera,i,j,width,height,ray --
            Ray ray;

            // Shoot ray and collect color -- in : ray,1.0,objects,lights,0,rgb --

            // Write double precision color into image
            auto clamp = [](double s){return max(min(s,1.0),0.0);};
            rgb_image[0+3*(j+width*i)] = 255.0*clamp(background_color.r);
            rgb_image[1+3*(j+width*i)] = 255.0*clamp(background_color.g);
            rgb_image[2+3*(j+width*i)] = 255.0*clamp(background_color.b);
        }
    }

    // write to file -- in : str filename, rgb_image, width, height, 3
}
