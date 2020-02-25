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
    file.write(reinterpret_cast<const char*>(&image_buffer[0]), image_buffer.size()*sizeof(unsigned char));
    file.clear();
    file.close();
}
