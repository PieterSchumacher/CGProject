#include "Object.h"
#include "Ray.h"
#include "Camera.h"
#include "Light.h"
#include "RGB.h"
#include <vector>
#include <memory>
#include <write_ppm.h>
#include <Intersection.h>
#include <PointLight.h>
#include <lambertian_reflection.h>
#include <ctime>
#include <chrono>
#include "Eigen/Dense"
#include <random>
#include <WaveFrontParser.h>
#include <Plane.h>
#include <sampling.h>
#include <AreaLight.h>
#include <Sphere.h>

void initialize_scene(vector<shared_ptr<Object>> &objects, vector<shared_ptr<Light>> &lights,
                      shared_ptr<Sampler> ptr);

using Eigen::Vector3d;
using std::max;
using std::min;
using std::vector;
using std::shared_ptr;
using Eigen::Matrix3d;

int main(int argc, char * argv[]) {
    const unsigned int h_res = 1024;
    const unsigned int v_res = 768;
    const float s = 0.003125; // pixel size
    const double plane_offset = 1.0;
    const double gamma = 2.2;
    const double super_sampling_rate = 5;
    const double N = pow(super_sampling_rate,2);
    const double delta = s / super_sampling_rate;

    std::clock_t c_start = std::clock();

    auto t_start = std::chrono::high_resolution_clock::now();
    Camera camera = Camera(
            Vector3d(1,1.5,-1.5),
            Vector3d(0,0,0),
            plane_offset,
            (double) h_res, (double) v_res,
            s);

    vector<shared_ptr<Object>>  objects;
    vector<shared_ptr<Light>>   lights;
    shared_ptr<Sampler> sampler(new Sampler());
    initialize_scene(objects, lights, sampler);
    vector<unsigned char> rgb_image(3*h_res*v_res);
    vector<double> temp(3*h_res*v_res);
    // For each pixel (i,j)
    #pragma omp parallel for
    for (unsigned r=0; r < v_res; ++r) {
        for (unsigned c=0; c < h_res; ++c) {
            rgb L              = rgb(0,0,0);
            rgb pigment         = rgb(1, 0.98, 0.94);   // default pigment
            // For each supersample
            for (unsigned k=0; k < super_sampling_rate; ++k) {
                for (unsigned l=0; l < super_sampling_rate; ++l) {
                    double dr = (sampler->random()+k)*delta;
                    double dc = (sampler->random()+l)*delta;
                    // Shoot ray through pixel
                    Ray ray;
                    camera.shoot_ray(c + dc, r + dr, ray);
                    // Outgoing radiance value
                    L += Lo(ray, lights, objects);
                }
            }
            // pixel <- color
            rgb color = L * pigment / N;

            temp[0+3*(c+h_res*(v_res-r-1))] = color.r;
            temp[1+3*(c+h_res*(v_res-r-1))] = color.g;
            temp[2+3*(c+h_res*(v_res-r-1))] = color.b;
        }
    }
    auto clamp = [](double s){return max(min(s,1.0),0.0);};
    double max_radiance = *max_element(std::begin(temp), std::end(temp));
    for (unsigned i=0; i < rgb_image.size(); i++) {
        rgb_image[0 + i] = 255.0*pow(clamp(temp[0 + i] / max_radiance), 1/gamma);
        rgb_image[1 + i] = 255.0*pow(clamp(temp[1 + i] / max_radiance), 1/gamma);
        rgb_image[2 + i] = 255.0*pow(clamp(temp[2 + i] / max_radiance), 1/gamma);
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

void initialize_scene(vector<shared_ptr<Object>> &objects, vector<shared_ptr<Light>> &lights, shared_ptr<Sampler> sampler) {
    parseWaveFrontFile("../data/sphere.obj", objects, lights);
//    parseWaveFrontFile("../data/tetrahedron.obj", objects, lights);
//    parseWaveFrontFile("../data/torus.obj", objects, lights);
//    parseWaveFrontFile("../data/xyzrgb_dragon.obj", objects, lights);
//    parseWaveFrontFile("../data/table.obj", objects, lights);
//    parseWaveFrontFile("../data/cube/.obj", objects, lights);
//    parseWaveFrontFile("../data/icosahedron.obj", objects, lights);
    shared_ptr<Material> mat1(new Material);
    mat1->kd = rgb(1,1,1);
    shared_ptr<Material> mat2(new Material);
    mat2->kd = rgb(0.7,0.7,0.7);
//    shared_ptr<Material> mat3(new Material);
//    mat3->kd = rgb(0.8,0,0);
//    shared_ptr<Material> mat4(new Material);
//    mat4->kd = rgb(0,0.8,0);
//    shared_ptr<Material> mat5(new Material);
//    mat5->kd = rgb(0,0,0.8);
//    shared_ptr<Material> mat6(new Material);
//    mat6->kd = rgb(0.8,0,0.8);
//    shared_ptr<Material> mat7(new Material);
//    mat7->kd = rgb(0,0.8,0.8);
//    shared_ptr<Material> mat8(new Material);
//    mat8->kd = rgb(0.8,0.8,0.8);
//    shared_ptr<Material> mat9(new Material);
//    mat9->kd = rgb(1,0.2,1);
    shared_ptr<Plane> plane1(new Plane());
    plane1->point = Vector3d(0,0,0);
    plane1->normal = Vector3d(0,1,0);
    plane1->material = mat2;
    objects.push_back(plane1);
//    shared_ptr<Sphere> sphere1(new Sphere(1, Vector3d(0,1,6)));
//    sphere1->material = mat1;
//    objects.push_back(sphere1);
//    shared_ptr<Sphere> sphere2(new Sphere(1, Vector3d(1.2,1,6)));
//    sphere2->material = mat2;
//    objects.push_back(sphere2);
//    shared_ptr<Sphere> sphere5(new Sphere(1, Vector3d(2.4,1,6)));
//    sphere5->material = mat5;
//    objects.push_back(sphere5);
//    shared_ptr<Sphere> sphere6(new Sphere(1, Vector3d(-2.4,1,6)));
//    sphere6->material = mat6;
//    objects.push_back(sphere6);
//    shared_ptr<Sphere> sphere3(new Sphere(1, Vector3d(-1.2,1,6)));
//    sphere3->material = mat3;
//    objects.push_back(sphere3);
//    shared_ptr<Sphere> sphere4(new Sphere(1, Vector3d(-1.2,3,6)));
//    sphere4->material = mat4;
//    objects.push_back(sphere4);
//    shared_ptr<Sphere> sphere7(new Sphere(1, Vector3d(1.2,3,6)));
//    sphere7->material = mat7;
//    objects.push_back(sphere7);
//    shared_ptr<Sphere> sphere8(new Sphere(1, Vector3d(0,3,6)));
//    sphere8->material = mat8;
//    objects.push_back(sphere8);
//    shared_ptr<Sphere> sphere9(new Sphere(1, Vector3d(0,5,6)));
//    sphere9->material = mat1;
//    objects.push_back(sphere9);
//    shared_ptr<PointLight> pointLight1(new PointLight(Vector3d(0, 0, 4) + Vector3d(4, 4, 2)));
//    pointLight1->I = rgb(253, 218.0, 153.0);
//    lights.push_back(pointLight1);
//    shared_ptr<PointLight> pointLight2(new PointLight());
//    pointLight2->I = rgb(40.0, 253, 40.0);
//    pointLight2->p = Vector3d(0, 0, 4) + Vector3d(2, 1, -10);
//    lights.push_back(pointLight2);
//    shared_ptr<PointLight> pointLight3(new PointLight());
//    pointLight3->I = rgb(153.0, 153.0, 253);
//    pointLight3->p = Vector3d(0, 0, 4) + Vector3d(0, 5, -10);
//    lights.push_back(pointLight3);
    shared_ptr<AreaLight> areaLight1(new AreaLight(Vector3d(6, 2, 16) + Vector3d(-1, 1, -14),
                                                   Vector3d(6, 0, 16) + Vector3d(-1, 1, -12),
                                                   Vector3d(6, 2, 16) + Vector3d(-1, 3, -12), sampler));
    areaLight1->material = mat1;
    objects.push_back(areaLight1);
    lights.push_back(areaLight1);
}
