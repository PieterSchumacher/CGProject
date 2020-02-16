//
// Created by piete on 2/16/2020.
//

#ifndef CGPROJECT_WAVEFRONTPARSER_H
#define CGPROJECT_WAVEFRONTPARSER_H

#include "Light.h"
#include "Object.h"
#include <vector>
#include <memory>
using String = std::string;
using std::vector;
using std::shared_ptr;

void parseWaveFrontFile(
        String filename,
        vector<shared_ptr<Object>> & objects,
        vector<shared_ptr<Light>> & lights);

#endif //CGPROJECT_WAVEFRONTPARSER_H
