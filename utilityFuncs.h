#include "string"
#include <array>
#include <vector>
#pragma once

std::string intToSignedString(int i);
class vec3{
    public:
        std::array<double,3> arr;
        vec3(double i,double j, double k);
        vec3(double i[3]);
        vec3 operator+(const vec3 &ar);
        vec3 operator-(const vec3 &ar);
        vec3 operator*(const double &f);
        vec3 operator/(const double &f);
        double size();
    };

std::vector<double> getColumn(std::vector<vec3> data,int i, double scale);

bool InputDouble3(const char* label, double v[3]);