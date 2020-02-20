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
#include <Intersection.h>
#include <PointLight.h>
#include "Eigen/Dense"

using Eigen::Vector3d;
using std::max;
using std::min;
using std::vector;
using std::shared_ptr;

int main(int argc, char * argv[]) {
    unsigned int h_res = 640;
    unsigned int v_res = 360;
    double s = 0.003125; // pixel size
    double plane_offset = 0.5;
    Camera camera = {Vector3d(0,0,0),                                       // eye
                     Vector3d(1,0,0), Vector3d(0,0,1), Vector3d(0,-1,0),    // uvw
                     plane_offset,                                          // distance to plane
                     (double) h_res, (double) v_res                         // image dimensions
                    };

    vector<shared_ptr<Object>>  objects;
    vector<shared_ptr<Light>>   lights;
    // Initialize scene and camera
    shared_ptr<PointLight> pointLight(new PointLight());
    pointLight->I = rgb(100.0,100.0,100.0);
    pointLight->p = Vector3d(0,0,2);
    lights.push_back(pointLight);
    shared_ptr<Material> mat(new Material());
    mat->kd = rgb(0.3,0.5,1);
    shared_ptr<Sphere> sphere(new Sphere());
    sphere->center = Vector3d(0,2,0);
    sphere->radius = 0.5;
    sphere->material = mat;
    objects.push_back(sphere);

    vector<unsigned char> rgb_image(3*h_res*v_res);
    // For each pixel (i,j)
    #pragma omp parallel for
    for (unsigned r=0; r < v_res; ++r) {
        for (unsigned c=0; c < h_res; ++c) {
            // Shoot ray through pixel
            Ray ray = {camera.eye, Vector3d(s*(c - (h_res/2.0) + 0.5), // x coordinate in uv space
                                          1,                           // negative viewing direction
                                          s*(r - (v_res/2.0) + 0.5)    // y coordinate in uv space
                                          ).normalized()               // center of pixel
                      };
            // Compute nearest intersection
            Intersection intersection;
            bool did_intersect = find_nearest_intersection(objects, ray, plane_offset, intersection);
            // Compute color of nearest intersection
            rgb diffuse_light   = rgb(0, 0, 0);
            rgb specular_light  = rgb(0, 0, 0);
            rgb pigment         = rgb(1, 0.98, 0.94);   // default pigment
            if (did_intersect) {
                Vector3d l = ray.direction;
                Vector3d x = intersection.t * l;
                for (shared_ptr<Light> &light : lights) {
                    Vector3d dlight; double max_t;
                    light->direction(x, dlight, max_t);
                    diffuse_light += intersection.object->material->kd*rgb(255.0,0.0,0.0)*light->I
                                        *(x.dot(dlight)/(x.norm()*dlight.norm())); // values are too high
                }
//                  diffuse_light += rgb(255.0,0.0,0.0);
            }
            rgb color = (diffuse_light + specular_light) * pigment;
            // pixel <- color
            auto clamp = [](double s){return max(min(s,1.0),0.0);};
            rgb_image[0+3*(c+h_res*r)] = 255.0*clamp(color.r/255.0);
            rgb_image[1+3*(c+h_res*r)] = 255.0*clamp(color.g/255.0);
            rgb_image[2+3*(c+h_res*r)] = 255.0*clamp(color.b/255.0);
        }
    }
    // write to file -- in : str filename, rgb_image, h_res, v_res, 3
    std::string filename = "CGDemo";
    write_ppm(filename, rgb_image, h_res, v_res);
}
