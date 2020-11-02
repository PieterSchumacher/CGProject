#include <write_ppm.h>
#include <memory>
#include <utility>
#include "WaveFrontParser.h"

using Eigen::Vector3d;
using Eigen::Vector2d;
using std::vector;
using std::unique_ptr;
using std::shared_ptr;
extern vector<shared_ptr<Vector3d>> normal_map;

void parseTexture(const String& filename, const shared_ptr<Material>& mat) {
    char pSix[10];
    int width, height, maximum = 0;
    std::ifstream file(filename, ios::in | ios::binary);
    file >> pSix >> width >> height >> maximum;
    char delimiter;
    file.read(&delimiter, 1);
    // Read RGB data.
    const int data_begin = file.tellg();
    file.seekg(0, file.end);
    const int data_end = file.tellg();
    file.seekg(data_begin, file.beg);
    const int data_size = data_end - data_begin;
    if (data_size != 3 * width * height) {
        cout << ("Failed to read PPM, unexpected data size %s.", filename.c_str());
    }
    vector<unsigned char> image_buffer = std::vector<unsigned char>(std::istreambuf_iterator<char>(file),
                                                                    std::istreambuf_iterator<char>());
    for (unsigned i=0; i < image_buffer.size() / 3; i++) {
        texture.push_back(std::make_shared<rgb>(image_buffer[0 + i*3], image_buffer[1 + i*3], image_buffer[2 + i*3]));
    }
}

void parseNormalMap(String filename) {
    char pSix[10];
    int width, height, maximum = 0;
    std::ifstream file(filename, ios::in | ios::binary);
    file >> pSix >> width >> height >> maximum;
    char delimiter;
    file.read(&delimiter, 1);
    // Read RGB data.
    const int data_begin = file.tellg();
    file.seekg(0, file.end);
    const int data_end = file.tellg();
    file.seekg(data_begin, file.beg);
    const int data_size = data_end - data_begin;
    if (data_size != 3 * width * height) {
        cout << ("Failed to read PPM, unexpected data size %s.", filename.c_str());
    }
    vector<unsigned char> image_buffer = std::vector<unsigned char>(std::istreambuf_iterator<char>(file),
                                                                    std::istreambuf_iterator<char>());
    for (unsigned i=0; i < image_buffer.size() / 3; i++) {
        normal_map.push_back(std::make_shared<Vector3d>(image_buffer[0 + i*3], image_buffer[1 + i*3], image_buffer[2 + i*3]));
    }
}

void parseWaveFrontFile(const String& filename, shared_ptr<BVH>& bvh) {
    vector<shared_ptr<Vector3d>> vertexes, normals;
    vector<shared_ptr<Vector2d>> textures;
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
                    shared_ptr<Vector2d> vertex(new Vector2d());
                    vertex->x() = u;
                    vertex->y() = v;
                    textures.push_back(vertex);
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
                vertices    << *vertexes[v1], *vertexes[v2], *vertexes[v3];
                norms       << *normals[vn1], *normals[vn2], *normals[vn3];
                shared_ptr<Triangle> triangle(new Triangle(vertices, norms, *textures[vt1], *textures[vt2], *textures[vt3]));
                shared_ptr<Material> mat1(new Material());
//                mat1->kd = rgb(0.823529,0.4117647,0.117647) * 0.3;
                mat1->kd = rgb(0.25098,0.84158,0.815686)*0.3;
//                mat1->kd = rgb(1,1,1)*0.1;
                triangle->material = mat1;
                triangles.push_back(triangle);
            } break;
        }
    }
    bvh = top_down(triangles);
//    shared_ptr<Material> mat1(new Material());
//    mat1->kd = rgb(0.25098,0.84158,0.815686);
//    bvh->material = mat1;
//    scene_objects.push_back(bvh);
}

