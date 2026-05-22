#include "string"
#include <array>
#include <vector>
#pragma once

std::string intToSignedString(int i);
struct vec3{
        std::array<double,3> arr;
        vec3(double i,double j, double k);
        vec3(double i[3]);
        vec3 operator+(const vec3 &ar);
        vec3 operator-(const vec3 &ar);
        vec3 operator*(const double &f);
        vec3 operator/(const double &f);
        std::string print(bool out=true);
        double size();
    };

    vec3 average3(std::vector<vec3> vecs);
struct vec2{
        std::array<double,2> arr;
        vec2(double i = 0,double j = 0);
        vec2(double i[2]);
        vec2 operator+(const vec2 &ar);
        vec2 operator-(const vec2 &ar);
        vec2 operator*(const double &f);
        vec2 operator/(const double &f);
        double size();
    };

std::vector<double> getColumn(std::vector<vec3> data,int i, double scale);
std::vector<double> getColumn(std::vector<vec2> data,int i, double scale);

bool InputDouble3(const char* label, double v[3]);