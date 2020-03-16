#include <fstream>
#include "WaveFrontParser.h"
#include "Triangle.h"
#include "TriangleMesh.h"
#include <memory>
#include <vector>
#include <BVH.h>

using Eigen::Vector3d;
using std::vector;
using std::shared_ptr;
void parseWaveFrontFile(
        String filename,
        vector<shared_ptr<Object>> & objects,
        vector<shared_ptr<Light>> & lights) {
    vector<shared_ptr<Vector3d>> vertexes, normals;
    vector<shared_ptr<Object>> triangles;
    String s;
    std::ifstream fin(filename);
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
                    fin >> x >> y >> z;
                    shared_ptr<Vector3d> vertex(new Vector3d());
                    vertex->x() = x;
                    vertex->y() = y;
                    vertex->z() = z;
                    normals.push_back(vertex);
                } else {
                    double x, y, z;
                    fin >> x >> y >> z;
                    shared_ptr<Vector3d> vertex(new Vector3d());
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
                v1 = temp[0] - 1; vt1 = temp[1] - 1; vn1 = temp[2] - 1;
                v2 = temp[3] - 1; vt2 = temp[4] - 1; vn2 = temp[5] - 1;
                v3 = temp[6] - 1; vt3 = temp[7] - 1; vn3 = temp[8] - 1;
                Matrix3d vertices, norms;
                vertices  << (*vertexes[v1] + Vector3d(0,-1.3,0)), (*vertexes[v2] + Vector3d(0,-1.3,0)), (*vertexes[v3] + Vector3d(0,-1.3,0));
                norms   << *normals[vn1], *normals[vn2], *normals[vn3];
                shared_ptr<Triangle> triangle(new Triangle(vertices, norms));
                shared_ptr<Material> mat1(new Material());
                mat1->kd = rgb(1.0,1.0,1.0);
                triangle->material = mat1;
                triangles.push_back(triangle);
            } break;
        }
    }
    shared_ptr<BVH> bvh = top_down(triangles, 2);
    shared_ptr<Material> mat1(new Material());
    mat1->kd = rgb(0.8,0,0.05);
    bvh->material = mat1;
    objects.push_back(bvh);
}

