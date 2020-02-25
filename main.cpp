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
#include "Eigen/Dense"

void initialize_scene(vector<shared_ptr<Object>> &objects, vector<shared_ptr<Light>> &lights) ;

using Eigen::Vector3d;
using std::max;
using std::min;
using std::vector;
using std::shared_ptr;
using Eigen::Matrix3d;

int main(int argc, char * argv[]) {
    const unsigned int h_res = 640;
    const unsigned int v_res = 360;
    const double s = 0.003125; // pixel size
    const double plane_offset = 1.0;
    const double gamma = 2.2;
    Camera camera = Camera(
            Vector3d(2, -1, 3),
            Vector3d(0,4,0),
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
            bool did_intersect = find_nearest_intersection(objects, ray, -1e-6, intersection);
            // Compute color of nearest intersection
            rgb diffuse_light   = rgb(0, 0, 0);
            rgb specular_light  = rgb(0, 0, 0);
            rgb pigment         = rgb(1, 0.98, 0.94);   // default pigment
            if (did_intersect) {
                compute_reflected_light(diffuse_light, specular_light, lights, objects, intersection.n,
                                        ray.eye + intersection.t * ray.direction);
            }
            rgb color = (diffuse_light + specular_light) * pigment;
            // pixel <- color
            auto clamp = [](double s){return max(min(s,255.0),0.0);};
            rgb_image[0+3*(c+h_res*r)] = clamp(color.r);
            rgb_image[1+3*(c+h_res*r)] = clamp(color.g);
            rgb_image[2+3*(c+h_res*r)] = clamp(color.b);
        }
    }
    // write to file
    std::string filename = "CGDemo";
    write_ppm(filename, rgb_image, h_res, v_res);
}

void initialize_scene(vector<shared_ptr<Object>> &objects, vector<shared_ptr<Light>> &lights) {
    shared_ptr<Material> mat(new Material());
    mat->kd = rgb(0.3,0.5,1);
    shared_ptr<Sphere> sphere1(new Sphere());
    sphere1->center = Vector3d(0, 1, 0);
    sphere1->radius = 1.0;
    sphere1->material = mat;
    objects.push_back(sphere1);
    shared_ptr<Sphere> sphere2(new Sphere());
    sphere2->center = Vector3d(1, 5, 0);
    sphere2->radius = 1.0;
    sphere2->material = mat;
    objects.push_back(sphere2);
    shared_ptr<Sphere> sphere3(new Sphere());
    sphere3->center = Vector3d(-1, 5, 0);
    sphere3->radius = 1.0;
    sphere3->material = mat;
    objects.push_back(sphere3);
//    shared_ptr<Triangle> triangle1(new Triangle());
//    triangle1->vertices = Matrix3d();
//    triangle1->vertices << Vector3d(-1.5, 4, -1), Vector3d(1.5, 4, -1), Vector3d(0, 4, 1.5);
//    triangle1->normals = Matrix3d();
//    triangle1->normals << Vector3d(0,-1,0),Vector3d(0,-1,0),Vector3d(0,-1,0);
//    objects.push_back(triangle1);
    shared_ptr<Plane> plane1(new Plane());
    plane1->point = Vector3d(-3,3,0);
    plane1->normal = Vector3d(0.5,-0.5,0.1);
    objects.push_back(plane1);
//    shared_ptr<AABB> aabb1(new AABB());
//    aabb1->v_min = Vector3d(-1,2,-1);
//    aabb1->v_max = Vector3d(1,3,1);
//    objects.push_back(aabb1);
    shared_ptr<PointLight> pointLight1(new PointLight());
    pointLight1->I = rgb(153.0, 0.0, 0.0);
    pointLight1->p = Vector3d(-2, 4, 0);
    lights.push_back(pointLight1);
    shared_ptr<PointLight> pointLight2(new PointLight());
    pointLight2->I = rgb(255.0, 147.0, 41.0);
    pointLight2->p = Vector3d(4, 2, 0);
    lights.push_back(pointLight2);
    shared_ptr<PointLight> pointLight3(new PointLight());
    pointLight3->I = rgb(0.0, 153.0, 0.0);
    pointLight3->p = Vector3d(2, 4, 0);
    lights.push_back(pointLight3);
}
