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
#include <Triangle.h>
#include <Plane.h>
#include <AABB.h>
#include <ctime>
#include <chrono>
#include <TriangleMesh.h>
#include "Eigen/Dense"
#include "omp.h"
#include <random>
#include <WaveFrontParser.h>

void initialize_scene(vector<shared_ptr<Object>> &objects, vector<shared_ptr<Light>> &lights) ;

using Eigen::Vector3d;
using std::max;
using std::min;
using std::vector;
using std::shared_ptr;
using Eigen::Matrix3d;

int main(int argc, char * argv[]) {
    const unsigned int h_res = 1920;
    const unsigned int v_res = 1080;
    const double s = 0.003125; // pixel size
    const double plane_offset = 1.0;
    const double gamma = 1.1;

    std::clock_t c_start = std::clock();

    auto t_start = std::chrono::high_resolution_clock::now();
    Camera camera = Camera(
            Vector3d(3,-4,5),
            Vector3d(0,6,0),
            plane_offset,
            (double) h_res, (double) v_res,
            s);

    vector<shared_ptr<Object>>  objects;
    vector<shared_ptr<Light>>   lights;
    initialize_scene(objects, lights);

    vector<unsigned char> rgb_image(3*h_res*v_res);
    // For each pixel (i,j)
//    #pragma omp parallel for
    for (unsigned r=0; r < v_res; ++r) {
        for (unsigned c=0; c < h_res; ++c) {
            // Shoot ray through pixel
            Ray ray;
            camera.shoot_ray(c, r, ray);
            // Compute nearest intersection
            Intersection intersection;
            bool did_intersect = find_nearest_intersection(objects, ray, 1e-6, intersection);
            // Compute color of nearest intersection
            rgb diffuse_light   = rgb(0, 0, 0);
            rgb specular_light  = rgb(0, 0, 0);
            rgb pigment         = rgb(1, 0.98, 0.94);   // default pigment
            if (did_intersect) {
                compute_reflected_light(diffuse_light, specular_light, lights, objects, intersection);
            }
            rgb color = (diffuse_light + specular_light) * pigment;
            // pixel <- color
            
            auto clamp = [](double s){return max(min(s,255.0),0.0);};
            rgb_image[0+3*(c+h_res*r)] = pow(clamp(color.r), 1/gamma);
            rgb_image[1+3*(c+h_res*r)] = pow(clamp(color.g), 1/gamma);
            rgb_image[2+3*(c+h_res*r)] = pow(clamp(color.b), 1/gamma);
        }
    }

    std::clock_t c_end = std::clock();
    auto t_end = std::chrono::high_resolution_clock::now();
    std::cout << std::fixed << "CPU time used: "
              << 1000.0 * (c_end-c_start) / CLOCKS_PER_SEC << " ms\n"
              << "Wall clock time passed: "
              << std::chrono::duration<double, std::milli>(t_end-t_start).count()
              << " ms\n";
    // write to file
    std::string filename = "CGDemo";
    write_ppm(filename, rgb_image, h_res, v_res);

}

void initialize_scene(vector<shared_ptr<Object>> &objects, vector<shared_ptr<Light>> &lights) {
    std::uniform_real_distribution<double> unif(0, 100);
    std::default_random_engine re;
    parseWaveFrontFile("../data/sphere.obj", objects, lights);
    shared_ptr<PointLight> pointLight1(new PointLight());
    pointLight1->I = rgb(253, 40.0, 40.0);
    pointLight1->p = Vector3d(0, 4, 0) + Vector3d(-3.5, -7, 1);
    lights.push_back(pointLight1);
    shared_ptr<PointLight> pointLight2(new PointLight());
    pointLight2->I = rgb(40.0, 253, 40.0);
    pointLight2->p = Vector3d(0, 4, 0) + Vector3d(3.5, -7, 1);
    lights.push_back(pointLight2);
    shared_ptr<PointLight> pointLight3(new PointLight());
    pointLight3->I = rgb(40.0, 40.0, 253);
    pointLight3->p = Vector3d(0, 4, 0) + Vector3d(0, -7, 5);
    lights.push_back(pointLight3);
}
