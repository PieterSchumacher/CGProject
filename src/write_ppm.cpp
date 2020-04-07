#include <cstring>
#include <cmath>
#include <RGB.h>
#include "write_ppm.h"
void read_ppm(const string& filename, vector<unsigned char>& image_buffer) {
    char pSix[10];
    int width, height, maximum = 0;
    std::ifstream file(filename, ios::binary);
    file >> pSix >> width >> height >> maximum;
    image_buffer = std::vector<unsigned char>(std::istreambuf_iterator<char>(file),
                                              std::istreambuf_iterator<char>());
}

void write_ppm(const string& filename, vector<unsigned char> image_buffer, unsigned int width, unsigned int height) {
    string filepath = "../images/" + filename + ".ppm";
    size_t size = width*height*3;
    ofstream file;
    file.open(filepath, ios::out | ios::binary);
    file << "P6" <<"\n";
    file << width << "\n";
    file << height << "\n";
    file << "255" << "\n";
    file.write(reinterpret_cast<const char*>(&image_buffer[0]), image_buffer.size()*sizeof(unsigned char));
    file.clear();
    file.close();
}

void write_txt(double nb_intersections) {
    string filepath = "../images/results.txt";
    ofstream file;
    file.open(filepath, ios::out | ios::binary);
    file << nb_intersections / 1e3 <<"\n";
    file.clear();
    file.close();
}

