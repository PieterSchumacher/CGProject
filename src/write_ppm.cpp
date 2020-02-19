#include "write_ppm.h"

void write_ppm(string filename, vector<unsigned char> image_buffer, unsigned int width, unsigned int height) {
    string filepath = "../images/" + filename + ".ppm";
    size_t size = width*height*3;
    ofstream file;
    file.open(filepath, ios::out | ios::binary);
    file << "P6" <<"\n";
    file << width << "\n";
    file << height << "\n";
    file << "255" << "\n";
    unsigned char temp[size];
    for (unsigned i=0; i < height; ++i) {
        for (unsigned j = 0; j < width; ++j) {
            temp[0 + 3*(j+width*i)] = image_buffer[0 + 3*(j+width*i)];
            temp[1 + 3*(j+width*i)] = image_buffer[1 + 3*(j+width*i)];
            temp[2 + 3*(j+width*i)] = image_buffer[2 + 3*(j+width*i)];
        }
    }
    file.write((char *)temp, size);
    file.clear();
    file.close();
}
