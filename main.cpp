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
#include <ctime>
#include <chrono>
#include "Eigen/Dense"
#include <random>
#include <WaveFrontParser.h>
#include <AABB.h>
#include <Plane.h>
#include <Triangle.h>
#include <BVH.h>

void initialize_scene(vector<shared_ptr<Object>> &objects, vector<shared_ptr<Light>> &lights) ;

using Eigen::Vector3d;
using std::max;
using std::min;
using std::vector;
using std::shared_ptr;
using Eigen::Matrix3d;

int main(int argc, char * argv[]) {
    const unsigned int h_res = 640;
    const unsigned int v_res = 380;
    const float s = 0.003125; // pixel size
    const double plane_offset = 1.0;
    const double gamma = 1.6;
    const double super_sampling_rate = 1;
    const double N = pow(super_sampling_rate,2);
    const double delta = s / super_sampling_rate;

    std::clock_t c_start = std::clock();

    auto t_start = std::chrono::high_resolution_clock::now();
    Camera camera = Camera(
            Vector3d(2,2,-1),
            Vector3d(0,0.5,0),
            plane_offset,
            (double) h_res, (double) v_res,
            s);

    vector<shared_ptr<Object>>  objects;
    vector<shared_ptr<Light>>   lights;
    initialize_scene(objects, lights);

    vector<unsigned char> rgb_image(3*h_res*v_res);
    vector<double> temp(3*h_res*v_res);
    std::uniform_real_distribution<double> unif(0,1);
    std::default_random_engine re1;
    std::default_random_engine re2;
    // For each pixel (i,j)
    #pragma omp parallel for
    for (unsigned r=0; r < v_res; ++r) {
        for (unsigned c=0; c < h_res; ++c) {
            rgb diffuse_light   = rgb(0, 0, 0);
            rgb specular_light  = rgb(0, 0, 0);
            rgb pigment         = rgb(1, 0.98, 0.94);   // default pigment
            // For each supersample
            for (unsigned k=0; k < super_sampling_rate; ++k) {
                for (unsigned l=0; l < super_sampling_rate; ++l) {
                    double dr = (unif(re1)+k)*delta;
                    double dc = (unif(re2)+l)*delta;
                    // Shoot ray through pixel
                    Ray ray;
                    camera.shoot_ray(c + dc, r + dr, ray);
                    // Compute nearest intersection
                    Intersection intersection;
                    bool did_intersect = find_nearest_intersection(objects, ray, 1e-6, intersection);
                    // Compute color of nearest intersection
                    if (did_intersect) {
                        compute_reflected_light(diffuse_light, specular_light, lights, objects, intersection);
                    }
                }
            }
            // pixel <- color
            rgb color = (diffuse_light + specular_light) * pigment / N;

            temp[0+3*(c+h_res*r)] = color.r;
            temp[1+3*(c+h_res*r)] = color.g;
            temp[2+3*(c+h_res*r)] = color.b;
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

void initialize_scene(vector<shared_ptr<Object>> &objects, vector<shared_ptr<Light>> &lights) {
//    parseWaveFrontFile("../data/sphere.obj", objects, lights);
//    parseWaveFrontFile("../data/tetrahedron.obj", objects, lights);
//    parseWaveFrontFile("../data/torus.obj", objects, lights);
//    parseWaveFrontFile("../data/table.obj", objects, lights);
//    parseWaveFrontFile("../data/cube.obj", objects, lights);
    parseWaveFrontFile("../data/icosahedron.obj", objects, lights);
    shared_ptr<Material> mat1(new Material);
    mat1->kd = rgb(1,1,1);
    shared_ptr<Material> mat2(new Material);
    mat2->kd = rgb(0,0,1);
//    shared_ptr<AABB> aabb1(new AABB(Vector3d(-1,0,-1), Vector3d(1, 1.6903, 1)));
//    aabb1->material = mat1;
//    objects.push_back(aabb1);
    shared_ptr<Plane> plane1(new Plane());
    plane1->point = Vector3d(0,0,0);
    plane1->normal = Vector3d(0,1,0);
    plane1->material = mat1;
    objects.push_back(plane1);
//    Vector3d c(0,1,0);
//    double radius = 0.3;
//    shared_ptr<Sphere> sphere1(new Sphere(radius, c));
//    sphere1->material = mat1;
//    objects.push_back(sphere1);
//    Matrix3d vertices1, normals1;
//    vertices1 << Vector3d(-1,0.5,0),Vector3d(1,0.5,0),Vector3d(0,1.5,0);
//    normals1 << Vector3d(0,0,-1),Vector3d(0,0,-1),Vector3d(0,0,-1);
//    shared_ptr<Triangle> triangle1(new Triangle(vertices1, normals1));
//    triangle1->material = mat1;
//    Matrix3d vertices2, normals2;
//    vertices2 << Vector3d(-0.5,0.8,-0.3),Vector3d(0.5,0.8,-0.3),Vector3d(0,1.3,-0.3);
//    normals2 << Vector3d(0,0,-1),Vector3d(0,0,-1),Vector3d(0,0,-1);
//    shared_ptr<Triangle> triangle2(new Triangle(vertices2, normals2));
//    triangle2->material = mat2;
//    Matrix3d vertices3, normals3;
//    vertices3 << Vector3d(-0.5,0.8,-0.6),Vector3d(0.5,0.8,-0.6),Vector3d(0,1.3,-0.6);
//    normals3 << Vector3d(0,0,-1),Vector3d(0,0,-1),Vector3d(0,0,-1);
//    shared_ptr<Triangle> triangle3(new Triangle(vertices3, normals3));
//    triangle3->material = mat2;
//    vector<shared_ptr<Object>> triangles;
//    triangles.push_back(triangle1);
//    triangles.push_back(triangle2);
////    triangles.push_back(triangle3);
//    shared_ptr<BVH> bvh = top_down(triangles, 2);
//    bvh->material = mat1;
//    objects.push_back(bvh);
    shared_ptr<PointLight> pointLight1(new PointLight());
    pointLight1->I = rgb(253, 40.0, 40.0);
    pointLight1->p = Vector3d(0, 0, 4) + Vector3d(-3.5, 1, -7);
    lights.push_back(pointLight1);
    shared_ptr<PointLight> pointLight2(new PointLight());
    pointLight2->I = rgb(40.0, 253, 40.0);
    pointLight2->p = Vector3d(0, 0, 4) + Vector3d(3.5, 1, -7);
    lights.push_back(pointLight2);
    shared_ptr<PointLight> pointLight3(new PointLight());
    pointLight3->I = rgb(153.0, 153.0, 253);
    pointLight3->p = Vector3d(0, 0, 4) + Vector3d(0, 5, -7);
    lights.push_back(pointLight3);
}
