#include <vector>
#include <iostream>
#include "../../utilityFuncs.h"
#include "../../dataStructs/vecs.h"
#include "../../dataStructs/scalarField.h"
#include "../../dataStructs/vectorField2.h"
#pragma once



struct mesh{
    int size;
    int nx;
    int ny;

    float Lx;
    float Ly;

    double h;

    vec2 Bleft;
    vec2 Bright;
    vec2 Btop;
    vec2 Bbottom;

    std::array<vec2*,4> BCs;
    std::array<int(mesh::*)(int), 4> sides;

    vectorField2 u;
    scalarField uDiag;
    scalarField p;
    scalarField pCorr;

    mesh(int nx_, float Lx_, int ny_)
        :
        size(nx_ * ny_),
        nx(nx_),
        ny(ny_),

        Lx(Lx_),
        Ly(Lx_ * ny_ / nx_),

        h(Lx_ / nx_),

        Bleft(0,0),
        Bright(0,0),
        Btop(1.0,0),
        Bbottom(0,0),

        BCs{&Btop,&Bright,&Bbottom,&Bleft},
        sides{&mesh::north,&mesh::east,&mesh::south,&mesh::west},

        u(nx_, ny_),
        uDiag(nx_, ny_),
        p(nx_, ny_),
        pCorr(nx_, ny_)
    {

    }

    void update(){
        u=vectorField2(nx, ny);
        uDiag=scalarField(nx, ny);
        p=scalarField(nx, ny);
        pCorr=scalarField(nx, ny);
        Ly=(Lx * ny / nx);
        h=(Lx / nx);
        size=nx*ny;
    }

    int east(int i);
    int west(int i);
    int north(int i);
    int south(int i);
};

vectorField2 GaussSeidel(scalarField A, vectorField2 b);
scalarField GaussSeidel(scalarField A, scalarField b);

scalarField AssembleUCoefficientMatrix(mesh& m, double mu);
vectorField2 AssembleURightSide(mesh& m, double mu);
scalarField AssemblePCoefficientMatrix(mesh& m, float alpha);
scalarField ComputeDivU(mesh& m);
vectorField2 ComputePressureGradient(mesh& m,bool corr);
void SolveVelocityField(mesh& m, double mu); 
void SolvePressureField(mesh& m, float alpha);
void SIMPLE(mesh* m);