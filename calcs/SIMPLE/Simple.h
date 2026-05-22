#include <vector>
#include "../../utilityFuncs.h"

struct scalarField{
std::vector<double> data;
int size;
int nx;
int ny;

scalarField(int nx_, int ny_){
    size=nx_ * ny_;
    nx=nx_;
    ny=ny_;
    for (int i=0; i<size; i++){
        data.push_back(0);
    }
};

double& operator()(int i, int j) {
        return data[i + j * size];
    }

double& operator()(int i) {
        return data[i];
    }

scalarField& operator+(const scalarField &ar) {
        if (nx==ar.nx && ny==ar.ny){
            scalarField sum = scalarField(nx,ny);
            for (int i=0;i<size;i++){
                sum(i)=data[i]+ar.data[i];
            }
            return sum;
        }
        else{std::cerr<<"field dimensions don't match"<<std::endl;}
    }

scalarField& operator-(const scalarField &ar) {
        if (nx==ar.nx && ny==ar.ny){
            scalarField sum = scalarField(nx,ny);
            for (int i=0;i<size;i++){
                sum(i)=data[i]-ar.data[i];
            }
            return sum;
        }
        else{std::cerr<<"field dimensions don't match"<<std::endl;}
    }
};

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

    vec2& operator()(int i, int j) {
            return data[i + j * size];
        }
    vec2& operator()(int i) {
        return data[i];
    }

    vectorField2& operator+(const vectorField2 &ar) {
        if (nx==ar.nx && ny==ar.ny){
            vectorField2 sum = vectorField2(nx,ny);
            for (int i=0;i<size;i++){
                sum(i)=data[i]+ar.data[i];
            }
            return sum;
        }
        else{std::cerr<<"field dimensions don't match"<<std::endl;}
    }

vectorField2& operator-(const vectorField2 &ar) {
        if (nx==ar.nx && ny==ar.ny){
            vectorField2 sum = vectorField2(nx,ny);
            for (int i=0;i<size;i++){
                sum(i)=data[i]-ar.data[i];
            }
            return sum;
        }
        else{std::cerr<<"field dimensions don't match"<<std::endl;}
    }
};



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
    std::array<vec2*,4> BCs={&Btop,&Bright,&Bbottom,&Bleft};
    std::array<int(mesh::*)(int), 4> sides={ &mesh::north,&mesh::east,&mesh::south,&mesh::west};
    mesh(int nx_, float Lx_, int ny_){
        size = nx_ * ny_;
        Lx=Lx_;
        nx = nx_;
        ny = ny_;
        Ly = Lx * ny / nx;
        
        h = Lx/nx;
        Bleft = vec2(0,0);
        Bright = vec2(0,0);
        Btop = vec2(0,0);
        Bbottom = vec2(0,0);

    }
    vectorField2 u = vectorField2(nx, ny);
    scalarField p = scalarField(nx, ny);

    bool isNeighbour(int i, int j);
    int boundaryN(int i);
    int east(int i);
    int west(int i);
    int north(int i);
    int south(int i);
};

vectorField2 GaussSeidel(scalarField A, vectorField2 b);

scalarField AssembleCoefficientMatrix(mesh m, double mu);
vectorField2 AssembleRightSide(mesh m, double mu);
vectorField2 ComputePressureGradient(mesh m);
void SolveVelocityField(mesh m, double mu);