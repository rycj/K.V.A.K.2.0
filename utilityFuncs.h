#include "string"
#include "dataStructs/vecs.h"
#include <array>
#include <vector>
#pragma once

std::string intToSignedString(int i);

std::vector<double> getColumn(std::vector<vec3> data,int i, double scale);
std::vector<double> getColumn(std::vector<vec2> data,int i, double scale);

bool InputDouble3(const char* label, double v[3]);
bool InputDouble2(const char* label, double v[2]);