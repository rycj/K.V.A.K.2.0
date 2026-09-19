#include <vector>
#include <iostream>
#include "vectorField2.h"
#pragma once

struct scalarField
{
    std::vector<double> data;
    int size;
    int nx;
    int ny;

    scalarField(int nx_, int ny_)
    {
        size = nx_ * ny_;
        nx = nx_;
        ny = ny_;
        for (int i = 0; i < size; i++)
        {
            data.push_back(0);
        }
    };

    double &operator()(int i, int j);

    double &operator()(int i);

    scalarField operator+(const scalarField &ar);

    scalarField operator-(const scalarField &ar);

    scalarField operator*(const double &a);

    vectorField2 operator*(const vectorField2 &ar);

    scalarField inverseVals();

    std::vector<double> getRow(int i);

    scalarField operator/(const double &a);

    scalarField diag(vec2 origSize);

    void chDiag(float multiplier);

    void scalarField::printGrid(int precision = 6);
};