//
// Created by piete on 2/19/2020.
//

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

void write_ppm(string filename, vector<unsigned char> image_buffer, unsigned int width, unsigned int height);

#endif //CGPROJECT_WRITE_PPM_H
