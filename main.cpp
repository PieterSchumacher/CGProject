#include "Object.h"
#include "Ray.h"
#include "Camera.h"
#include "Light.h"
#include "RGB.h"
#include <vector>
#include <memory>
#include <Sphere.h>
#include <write_ppm.h>
#include <Intersection.h>
#include <PointLight.h>
#include <lambertian_reflection.h>
#include "Eigen/Dense"

using Eigen::Vector3d;
using std::max;
using std::min;
using std::vector;
using std::shared_ptr;

int main(int argc, char * argv[]) {
    const unsigned int h_res = 640;
    const unsigned int v_res = 360;
    const double s = 0.003125; // pixel size
    const double plane_offset = 1.0;
    const double gamma = 2.2;
    Camera camera = {Vector3d(0,0,0),                                       // eye
                     Vector3d(1,0,0), Vector3d(0,0,1), Vector3d(0,-1,0),    // uvw
                     plane_offset,                                          // distance to plane
                     (double) h_res, (double) v_res                         // image dimensions
                    };

    vector<shared_ptr<Object>>  objects;
    vector<shared_ptr<Light>>   lights;
    // Initialize scene and camera
    shared_ptr<Material> mat(new Material());
    mat->kd = rgb(0.3,0.5,1);
    shared_ptr<Sphere> sphere(new Sphere());
    sphere->center = Vector3d(0,2,0);
    sphere->radius = 0.5;
    sphere->material = mat;
    objects.push_back(sphere);
    shared_ptr<PointLight> pointLight1(new PointLight());
    pointLight1->I = rgb(253.0, 0.0, 0.0);
    pointLight1->p = Vector3d(0, 0, -1);
    shared_ptr<PointLight> pointLight2(new PointLight());
    pointLight2->I = rgb(0.0, 0.0, 153.0);
    pointLight2->p = Vector3d(-1, 0, 0);
    shared_ptr<PointLight> pointLight3(new PointLight());
    pointLight3->I = rgb(0.0, 153.0, 0.0);
    pointLight3->p = Vector3d(1, 0, 0);
    lights.push_back(pointLight1);
    lights.push_back(pointLight2);
    lights.push_back(pointLight3);

    vector<unsigned char> rgb_image(3*h_res*v_res);
    // For each pixel (i,j)
    #pragma omp parallel for
    for (unsigned r=0; r < v_res; ++r) {
        for (unsigned c=0; c < h_res; ++c) {
            // Shoot ray through pixel
            Ray ray = {camera.eye, Vector3d(s*(c - (h_res/2.0) + 0.5),   // x coordinate in uv space
                                            plane_offset,                           // negative viewing direction
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
                compute_reflected_light(diffuse_light, specular_light, lights,
                                            intersection.t * ray.direction, intersection.n);
            }
            rgb color = (diffuse_light + specular_light) * pigment;
//            cout << color.r << " " << color.g << " " << color.b << " ";
            // pixel <- color
            auto clamp = [](double s){return max(min(s,255.0),0.0);};
            rgb_image[0+3*(c+h_res*r)] = clamp(color.r);
            rgb_image[1+3*(c+h_res*r)] = clamp(color.g);
            rgb_image[2+3*(c+h_res*r)] = clamp(color.b);
        }
    }
    // write to file -- in : str filename, rgb_image, h_res, v_res, 3
    std::string filename = "CGDemo";
    write_ppm(filename, rgb_image, h_res, v_res);
}
