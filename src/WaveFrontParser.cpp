#include <fstream>
#include "WaveFrontParser.h"
#include "Triangle.h"
#include "TriangleMesh.h"
#include <memory>
#include <vector>
#include "Eigen"
#include <iostream>
using Eigen::Vector3d;
using std::vector;
using std::shared_ptr;
void parseWaveFrontFile(
        String filename,
        vector<shared_ptr<Object>> & objects,
        vector<shared_ptr<Light>> & lights) {
    vector<shared_ptr<Vector3d>> vertexes, normals;
    shared_ptr<TriangleMesh> mesh(new TriangleMesh);
    String s;
    std::ifstream fin("../data/sphere.obj");
    if (!fin)
        return;
    while (fin >> s) {
        switch (*s.c_str()) {
            case 'v': {
                if (s[1] == 't') {
                    double u, v;
                    fin >> u >> v;
                } else if (s[1] == 'n') {
                    double x, y, z;
                    shared_ptr<Vector3d> vertex(new Vector3d);
                    fin >> x >> y >> z;
                    vertex->x() = x;
                    vertex->y() = y;
                    vertex->z() = z;
                    normals.push_back(vertex);
                } else {
                    double x, y, z;
                    shared_ptr<Vector3d> vertex;
                    fin >> x >> y >> z;
                    vertex->x() = x;
                    vertex->y() = y;
                    vertex->z() = z;
                    vertexes.push_back(vertex);
                }
            } break;
            case 'f': {
                unsigned int v1, vt1, vn1, v2, vt2, vn2, v3, vt3, vn3;
                String f1, f2, f3;
                fin >> f1 >> f2 >> f3;
                vector<unsigned int> temp;
                std::string token;
                std::stringstream ss1(f1);
                std::stringstream ss2(f2);
                std::stringstream ss3(f3);
                while (std::getline(ss1, token, '/')) {
                    temp.push_back(std::stoul(token));
                }
                while (std::getline(ss2, token, '/')) {
                    temp.push_back(std::stoul(token));
                }
                while (std::getline(ss3, token, '/')) {
                    temp.push_back(std::stoul(token));
                }
                v1 = temp[0]; vt1 = temp[1]; vn1 = temp[2];
                v2 = temp[3]; vt2 = temp[4]; vn2 = temp[5];
                v3 = temp[6]; vt3 = temp[7]; vn3 = temp[8];
                shared_ptr<Triangle> triangle(new Triangle);
                triangle->vertices  << *vertexes[v1], *vertexes[v2], *vertexes[v3];
                triangle->normals   << *normals[vn1], *normals[vn2], *normals[vn3];
                std::cout << vertexes[v1].get() << "\n";
                mesh->triangles.push_back(triangle);
            } break;
        }
    }
    shared_ptr<Material> mat1(new Material());
    mat1->kd = rgb(1.0,1.0,1.0);
    mesh->material = mat1;
    objects.push_back(mesh);
}

