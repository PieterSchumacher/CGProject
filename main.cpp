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
#include <random>
#include <WaveFrontParser.h>
#include <Plane.h>
#include <sampling.h>
#include <AreaLight.h>
#include <Sphere.h>

void initialize_scene();

using Eigen::Vector3d;
using std::max;
using std::min;
using std::vector;
using std::shared_ptr;
using Eigen::Matrix3d;

vector<shared_ptr<Object>> scene_objects;
vector<shared_ptr<Light>> lights;
shared_ptr<Sampler> sampler(new Sampler());
vector<shared_ptr<rgb>> texture;
vector<shared_ptr<Vector3d>> normal_map;
double nb_intersections = 0;
double a = 1.0;
int main(int argc, char * argv[]) {
    const unsigned int  h_res           = 1920;
    const unsigned int  v_res           = 1080;
    const float         s               = 0.003125; // pixel size
    const unsigned      plane_offset    = 12;
    const double        gamma           = 2.2;
    const unsigned      sample_rate     = 64;
    const double        N               = pow(sample_rate,2);
    const double        delta           = 1.0 / sample_rate;

    std::clock_t c_start = std::clock();

    auto t_start = std::chrono::high_resolution_clock::now();
    Camera camera = Camera(Vector3d(-0.5,3,-8),
                           Vector3d(-0.5,0.5,0),
                           plane_offset,
                           (double) h_res, (double) v_res,
                           s);
    double percentage = 0;
    initialize_scene();
    vector<unsigned char> rgb_image(3*h_res*v_res);
    vector<double> temp(3*h_res*v_res);
    // For each pixel (i,j)
    #pragma omp parallel for schedule(dynamic, 1) default(none) shared(scene_objects, lights, sampler, camera, temp, nb_intersections, percentage, cout)
    for (unsigned r=0; r < v_res; ++r) {
        for (unsigned c=0; c < h_res; ++c) {
            rgb L       = rgb(0,0,0);
            rgb pigment = rgb(1, 0.98, 0.94);   // default pigment
            // For each supersample
            for (unsigned k=0; k < sample_rate; ++k) {
                for (unsigned l=0; l < sample_rate; ++l) {
                    double dr = (sampler->random()+k)*delta;
                    double dc = (sampler->random()+l)*delta;
                    // Shoot ray through pixel
                    Ray ray;
                    camera.shoot_ray(c + dc, r + dr, ray);
                    // Add outgoing radiance value
                    L += Lo(ray);
                }
            }
            // pixel <- color
            rgb color = L * pigment / N;
            temp[0+3*(c+h_res*(v_res-r-1))] = color.r;
            temp[1+3*(c+h_res*(v_res-r-1))] = color.g;
            temp[2+3*(c+h_res*(v_res-r-1))] = color.b;
        }
        percentage += 1.0/v_res;
        cout << "percentage: " << percentage << "\n";
    }
    auto clamp = [](double s){return max(min(s,1.0),0.0);};
    double max_radiance = *max_element(std::begin(temp), std::end(temp));
    for (unsigned i=0; i < rgb_image.size() / 3; i++) {
        rgb_image[0 + i*3] = 255.0*pow(clamp(temp[0 + i*3] / max_radiance), 1/gamma);
        rgb_image[1 + i*3] = 255.0*pow(clamp(temp[1 + i*3] / max_radiance), 1/gamma);
        rgb_image[2 + i*3] = 255.0*pow(clamp(temp[2 + i*3] / max_radiance), 1/gamma);
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
    write_txt(nb_intersections);
}

void initialize_scene() {
//    shared_ptr<BVH> apple;
//    parseWaveFrontFile("../data/apple/apple.obj", apple);
//    shared_ptr<Material> mat_apple(new Material);
//    parseNormalMap("../data/apple/apple_normal.ppm");
//    parseTexture("../data/apple/apple_texture.ppm", mat_apple);
//    scene_objects.push_back(apple);
//    shared_ptr<BVH> dragon;
//    parseWaveFrontFile("../data/dragon.obj", dragon);
//    shared_ptr<Material> mat_drag(new Material);
//    dragon->material = mat_drag;
//    dragon->material->kd = rgb(0.25098,0.84158,0.815686);
//    dragon->material->ks = rgb(0,0,0);
//    dragon->material->kt = rgb(0.75,0.75,0.75);
//    dragon->material->nu = 5.0/3.0;
//    scene_objects.push_back(dragon);
    shared_ptr<BVH> teapot;
    parseWaveFrontFile("../data/teapot.obj", teapot);
    shared_ptr<Material> mat_tea(new Material);
    teapot->material = mat_tea;
//    teapot->material->kd = rgb(0.823529,0.4117647,0.117647);
    teapot->material->ks = rgb(1,1,1);
    teapot->material->kt = rgb(1,1,1);
    teapot->material->nu = 1.5;
    scene_objects.push_back(teapot);
    shared_ptr<Material> mat1(new Material);
    mat1->kd = rgb(1,1,1);
    mat1->ks = rgb(0,0,0);
    shared_ptr<Material> mat2(new Material);
    mat2->kd = rgb(0,1,0);
    mat2->ks = rgb(0,0,0);
    shared_ptr<Material> mat3(new Material);
    mat3->kd = rgb(1,0,0);
//    mat3->ks = rgb(0.75,0.75,0.75);
//    mat3->nu = 2;
    shared_ptr<Material> mat6(new Material);
    mat6->kd = rgb(1,0.05,0.15);
    mat6->ks = rgb(0,0,0);
    shared_ptr<Material> mat4(new Material);
    mat4->kd = rgb(1,1,1);
    mat4->ks = rgb(0,0,0);
    shared_ptr<Material> mat5(new Material);
    mat5->kd = rgb(0,0,1);
    mat5->ks = rgb(0,0,0);
    shared_ptr<Material> mat7(new Material);
    mat7->kd = rgb(0.25,0.05,1);
    mat7->ks = rgb(0,0,0);
    shared_ptr<Material> mat8(new Material);
    mat8->kd = rgb(0.5,0.5,0.5);
    mat8->ks = rgb(0.75,0.75,0.75);
    mat8->nu = 4;
    shared_ptr<Material> mat9(new Material);
    mat9->kd = rgb(0,0,0);
    mat9->ks = rgb(1,1,1);
    mat9->kt = rgb(1,1,1);
    mat9->nu = 3.2;
    shared_ptr<Plane> plane1(new Plane());
    plane1->point = Vector3d(0,0,0);
    plane1->normal = Vector3d(0,1,0);
    plane1->material = mat1;
    scene_objects.push_back(plane1);
    shared_ptr<Plane> plane2(new Plane());
    plane2->point = Vector3d(-5,0,0);
    plane2->normal = Vector3d(1,0,0);
    plane2->material = mat1;
    scene_objects.push_back(plane2);
    shared_ptr<Plane> plane3(new Plane());
    plane3->point = Vector3d(0,0,2);
    plane3->normal = Vector3d(0,0,-1);
    plane3->material = mat1;
//    scene_objects.push_back(plane3);
    shared_ptr<Plane> plane4(new Plane());
    plane4->point = Vector3d(0,4,0);
    plane4->normal = Vector3d(0,-1,0);
    plane4->material = mat1;
//    scene_objects.push_back(plane4);
    shared_ptr<Plane> plane5(new Plane());
    plane5->point = Vector3d(0,0,-5);
    plane5->normal = Vector3d(0,0,1);
    plane5->material = mat1;
//    scene_objects.push_back(plane5);
    shared_ptr<Plane> plane6(new Plane());
    plane6->point = Vector3d(5,0,0);
    plane6->normal = Vector3d(-1,0,0).normalized();
    plane6->material = mat9;
//    scene_objects.push_back(plane6);
//    shared_ptr<Sphere> sphere1(new Sphere(0.25, Vector3d(-0.75,2.75,1.75)));
//    sphere1->material = mat7;
//    scene_objects.push_back(sphere1);
//    shared_ptr<Sphere> sphere2(new Sphere(0.25, Vector3d(0.75,0.25,-1.75)));
//    sphere2->material = mat6;
//    scene_objects.push_back(sphere2);
//    shared_ptr<AABB> aabb1(new AABB(Vector3d(-1.75,0,-1), Vector3d(0, 1, 0)));
//    aabb1->material = mat1;
//    scene_objects.push_back(aabb1);
//    shared_ptr<Sphere> sphere3(new Sphere(0.3, Vector3d(3, 0.5, 0.5)));
//    sphere3->material = mat9;
//    scene_objects.push_back(sphere3);
//    shared_ptr<AreaLight> areaLight1(new AreaLight(Vector3d(0, 3, -0.5),
//                                                       Vector3d(0, 3, 0.5),
//                                                       Vector3d(1, 3, -0.5)));
//    areaLight1->material = mat1;
//    scene_objects.push_back(areaLight1);
//    lights.push_back(areaLight1);
    shared_ptr<AreaLight> areaLight1(new AreaLight(Vector3d(5, 0*a, -1.5*a),
                                                       Vector3d(5, 3*a, -1.5*a),
                                                       Vector3d(5, 0*a, 1.5*a)));
    areaLight1->material = mat1;
    scene_objects.push_back(areaLight1);
    lights.push_back(areaLight1);
    shared_ptr<AreaLight> areaLight3(new AreaLight(Vector3d(1.5, 5, -1.5) + Vector3d(-3.5,0,0),
                                                       Vector3d(-1.5, 5, -1.5) + Vector3d(-3.5,0,0),
                                                       Vector3d(1.5, 5, 1.5) + Vector3d(-3.5,0,0)));
    areaLight3->material = mat1;
//    scene_objects.push_back(areaLight3);
//    lights.push_back(areaLight3);
//    vector<unsigned char> texture;
//    read_ppm("../data/reptile_texture.ppm", texture);
}
