#include <vector>
#include <iostream>
#include "vectorField2.h"
#include "scalarField.h"
#include <cmath>
#include <iomanip>

double& scalarField::operator()(int i, int j) {
        return data[i + j * nx];
    }

double& scalarField::operator()(int i) {
        return data[i];
    }

scalarField scalarField::operator+(const scalarField &ar) {
        if (nx==ar.nx && ny==ar.ny){
            scalarField sum = scalarField(nx,ny);
            for (int i=0;i<size;i++){
                sum(i)=data[i]+ar.data[i];
            }
            return sum;
        }
        else{std::cout<<"field dimensions don't match"<<std::endl;}
    }

scalarField scalarField::operator-(const scalarField &ar) {
        if (nx==ar.nx && ny==ar.ny){
            scalarField sum = scalarField(nx,ny);
            for (int i=0;i<size;i++){
                sum(i)=data[i]-ar.data[i];
            }
            return sum;
        }
        else{std::cout<<"field dimensions don't match"<<std::endl;}
    }

scalarField scalarField::operator*(const double &a) {
    scalarField res = scalarField(nx,ny);
    for (int i=0;i<size;i++){
        res(i)=data[i]*a;
        }
        return res;
    }

vectorField2 scalarField::operator*(const vectorField2 &ar) {
    vectorField2 res(nx,ny);
    std::cout<<"fails here?"<<std::endl;
    for (int i=0;i<size;i++){
        // std::cout<<i<<"   "<<size<<"   "<<ar.size<<std::endl;
        res(i)=ar.data[i]*data[i];
        }

        return res;
    }

scalarField scalarField::inverseVals() {
    scalarField res = scalarField(nx,ny);
    std::cout<<"inverting"<<std::endl;
    for (int i=0;i<size;i++){
        res(i)=1.0/data[i];
        }
        std::cout<<"inverted"<<std::endl;
        return res;
    }

scalarField scalarField::operator/(const double &a) {
    scalarField res = scalarField(nx,ny);
    for (int i=0;i<size;i++){
        res(i)=data[i]/a;
        }
        return res;
    }

scalarField scalarField::diag(vec2 origSize){
    scalarField diagonal=scalarField(origSize(0),origSize(1));
    std::cout<<"diagsize in diag at start "<<diagonal.size<<std::endl;
    for (int i=0;i<origSize(0)*origSize(1);i++){
            diagonal(i)=this->operator()(this->ny-1-i,i);
        }
        std::cout<<"diagsize in diag at end "<<diagonal.size<<std::endl;
        return diagonal;
    }

void scalarField::chDiag(float multiplier){
    // assumes square matrix
    for (int i=0;i<this->ny;i++){
            this->operator()(i,i)=this->operator()(i,i)*multiplier;
        }
    }


void scalarField::printGrid(int precision)
{
    std::cout << "\nScalarField (" << nx << " x " << ny << ")\n";

    std::cout << std::fixed << std::setprecision(precision);

    auto printCell = [&](double v)
    {
        if (std::isnan(v))
            std::cout << std::setw(12) << "NaN";
        else if (std::isinf(v))
            std::cout << std::setw(12) << "Inf";
        else
            std::cout << std::setw(12) << v;
    };

    for (int j = ny - 1; j >= 0; --j)
    {
        for (int i = 0; i < nx; ++i)
        {
            double v = data[i + j * nx];
            printCell(v);
            std::cout << " ";
        }
        std::cout << "\n";
    }

    std::cout << std::defaultfloat;
}