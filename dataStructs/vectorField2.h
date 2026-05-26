#include <vector>
#include <iostream>
#include "vecs.h"
#pragma once

struct scalarField;
struct vectorField2{
std::vector<vec2> data;
int size;
int nx;
int ny;

    vectorField2(int nx_, int ny_){
        size=nx_ * ny_;
        nx=nx_;
        ny=ny_;
        for (int i=0; i<size; i++){
            data.push_back(vec2(0,0));
        }
    };

    vec2& operator()(int i, int j);
    
    vec2& operator()(int i);

    vectorField2 operator+(const vectorField2 &ar);

    vectorField2 operator-(const vectorField2 &ar);

    vectorField2 operator*(const double &a);

    scalarField magnitude();

    scalarField xs();

    scalarField ys();
};