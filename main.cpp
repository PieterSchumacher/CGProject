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
    #pragma omp parallel for
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
    std::uniform_real_distribution<double> unif(0,100);
    std::default_random_engine re;
    shared_ptr<Material> mat1(new Material());
    mat1->kd = rgb(1.0,1.0,1.0);
    for (int k = 0; k < 1000; ++k){
        shared_ptr<Material> mat6(new Material());
        mat6->kd = rgb(1, 1, 1);
        shared_ptr<Triangle> triangle1(new Triangle());
        triangle1->vertices = Matrix3d();
        triangle1->vertices << Vector3d(unif(re), unif(re), unif(re)), Vector3d(unif(re), unif(re), unif(re)), Vector3d(unif(re), unif(re), unif(re));
        Vector3d n = (triangle1->vertices.col(0) - triangle1->vertices.col(1)).cross(triangle1->vertices.col(2) - triangle1->vertices.col(1)).normalized();
        triangle1->normals = Matrix3d();
        triangle1->normals << n,n,n;
        triangle1->material = mat6;
        objects.push_back(triangle1);
    }
//    shared_ptr<Sphere> sphere1(new Sphere());
//    sphere1->center = Vector3d(unif(re),unif(re),unif(re));
//    sphere1->radius = 1.0;
//    sphere1->material = mat1;
//    objects.push_back(sphere1);
//    shared_ptr<Material> mat2(new Material());
//    mat2->kd = rgb(1.0,1.0,1.0);
//    shared_ptr<Sphere> sphere2(new Sphere());
//    sphere2->center = Vector3d(0,4,0) + Vector3d(1.5,0,1);
//    sphere2->radius = 1.0;
//    sphere2->material = mat2;
//    objects.push_back(sphere2);
//    shared_ptr<Material> mat3(new Material());
//    mat3->kd = rgb(1.0,1.0,1.0);
//    shared_ptr<Sphere> sphere3(new Sphere());
//    sphere3->center = Vector3d(0,4,0) + Vector3d(0,0,3);
//    sphere3->radius = 1.0;
//    sphere3->material = mat3;
//    objects.push_back(sphere3);
//
//    shared_ptr<Material> mat4(new Material());
//    mat4->kd = rgb(1.0,1.0,1.0);
//    shared_ptr<Plane> plane1(new Plane());
//    plane1->point = Vector3d(-3,3,0);
//    plane1->normal = Vector3d(0,0,1);
//    plane1->material = mat4;
//    objects.push_back(plane1);
//
//    shared_ptr<Material> mat5(new Material());
//    mat5->kd = rgb(0.8,0.4,1);
//    shared_ptr<AABB> aabb1(new AABB());
//    aabb1->v_min = Vector3d(6,2,0);
//    aabb1->v_max = Vector3d(9,6,2);
//    aabb1->material = mat5;
//    objects.push_back(aabb1);
//    triangle2->vertices = Matrix3d();
//    triangle2->vertices << Vector3d(-6, 4, 0), Vector3d(-6, 4, 2), Vector3d(-8, 4, 2);
//    n = -(triangle2->vertices.col(0) - triangle2->vertices.col(1)).cross(triangle2->vertices.col(2) - triangle2->vertices.col(1)).normalized();
//    triangle2->normals = Matrix3d();
//    triangle2->normals << n,n,n;
//    triangle2->material = mat6;
//    shared_ptr<Triangle> triangle3(new Triangle());
//    triangle3->vertices = Matrix3d();
//    triangle3->vertices << Vector3d(-6, 4, 0), Vector3d(-8, 6, 2), Vector3d(-8, 4, 2);
//    n = (triangle3->vertices.col(0) - triangle3->vertices.col(1)).cross(triangle3->vertices.col(2) - triangle3->vertices.col(1)).normalized();
//    triangle3->normals = Matrix3d();
//    triangle3->normals << n,n,n;
//    triangle3->material = mat6;
//    shared_ptr<Triangle> triangle4(new Triangle());
//    triangle4->vertices = Matrix3d();
//    triangle4->vertices << Vector3d(-6, 4, 0), Vector3d(-8, 6, 2), Vector3d(-6, 6, 2);
//    n = (triangle4->vertices.col(0) - triangle4->vertices.col(1)).cross(triangle4->vertices.col(2) - triangle4->vertices.col(1)).normalized();
//    triangle4->normals = Matrix3d();
//    triangle4->normals << n,n,n;
//    triangle4->material = mat6;
//    shared_ptr<Triangle> triangle5(new Triangle());
//    triangle5->vertices = Matrix3d();
//    triangle5->vertices << Vector3d(-6, 4, 4), Vector3d(-6, 4, 2), Vector3d(-6, 6, 2);
//    n = -(triangle5->vertices.col(0) - triangle5->vertices.col(1)).cross(triangle5->vertices.col(2) - triangle5->vertices.col(1)).normalized();
//    triangle5->normals = Matrix3d();
//    triangle5->normals << n,n,n;
//    triangle5->material = mat6;
//    shared_ptr<Triangle> triangle6(new Triangle());
//    triangle6->vertices = Matrix3d();
//    triangle6->vertices << Vector3d(-6, 4, 4), Vector3d(-6, 4, 2), Vector3d(-8, 4, 2);
//    n = (triangle6->vertices.col(0) - triangle6->vertices.col(1)).cross(triangle6->vertices.col(2) - triangle6->vertices.col(1)).normalized();
//    triangle6->normals = Matrix3d();
//    triangle6->normals << n,n,n;
//    triangle6->material = mat6;
//    shared_ptr<Triangle> triangle7(new Triangle());
//    triangle7->vertices = Matrix3d();
//    triangle7->vertices << Vector3d(-6, 4, 4), Vector3d(-8, 6, 2), Vector3d(-8, 4, 2);
//    n = (triangle7->vertices.col(0) - triangle7->vertices.col(1)).cross(triangle7->vertices.col(2) - triangle7->vertices.col(1)).normalized();
//    triangle7->normals = Matrix3d();
//    triangle7->normals << n,n,n;
//    triangle7->material = mat6;
//    shared_ptr<Triangle> triangle8(new Triangle());
//    triangle8->vertices = Matrix3d();
//    triangle8->vertices << Vector3d(-6, 4, 4), Vector3d(-8, 6, 2), Vector3d(-6, 6, 2);
//    n = (triangle8->vertices.col(0) - triangle8->vertices.col(1)).cross(triangle8->vertices.col(2) - triangle8->vertices.col(1)).normalized();
//    triangle8->normals = Matrix3d();
//    triangle8->normals << n,n,n;
//    triangle8->material = mat6;
//    shared_ptr<TriangleMesh> doublePyramid(new TriangleMesh());
//    doublePyramid->triangles.push_back(triangle1);
//    doublePyramid->triangles.push_back(triangle2);
//    doublePyramid->triangles.push_back(triangle3);
//    doublePyramid->triangles.push_back(triangle4);
//    doublePyramid->triangles.push_back(triangle5);
//    doublePyramid->triangles.push_back(triangle6);
//    doublePyramid->triangles.push_back(triangle7);
//    doublePyramid->triangles.push_back(triangle8);
//    doublePyramid->material = mat6;
//    objects.push_back(doublePyramid);

    shared_ptr<PointLight> pointLight1(new PointLight());
    pointLight1->I = rgb(253, 40.0, 40.0);
    pointLight1->p = Vector3d(0,4,0) + Vector3d(-3.5,-7,1);
    lights.push_back(pointLight1);
    shared_ptr<PointLight> pointLight2(new PointLight());
    pointLight2->I = rgb(40.0, 253, 40.0);
    pointLight2->p = Vector3d(0,4,0) + Vector3d(3.5,-7,1);
    lights.push_back(pointLight2);
    shared_ptr<PointLight> pointLight3(new PointLight());
    pointLight3->I = rgb(40.0, 40.0, 253);
    pointLight3->p = Vector3d(0,4,0) + Vector3d(0,-7,5);
    lights.push_back(pointLight3);
}
