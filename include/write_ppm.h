#ifndef CGPROJECT_WRITE_PPM_H
#define CGPROJECT_WRITE_PPM_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>


using std::string;
using std::vector;
using std::cout;
using std::size_t;
using std::ofstream;
using std::ios;

void read_ppm(const string& filename, vector<unsigned char>& image_buffer);
void write_txt(double nb_intersections);
void write_ppm(const string& filename, vector<unsigned char> image_buffer, unsigned int width, unsigned int height);

#endif //CGPROJECT_WRITE_PPM_H
