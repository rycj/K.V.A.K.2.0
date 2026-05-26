#include <vector>
#include <iostream>
#include "vecs.h"
#include "vectorField2.h"
#include "scalarField.h"

    vec2& vectorField2::operator()(int i, int j) {
            return data[i + j * nx];
        }
    vec2& vectorField2::operator()(int i) {
        return data[i];
    }

    vectorField2 vectorField2::operator+(const vectorField2 &ar) {
        if (nx==ar.nx && ny==ar.ny){
            vectorField2 sum = vectorField2(nx,ny);
            for (int i=0;i<size;i++){
                sum(i)=data[i]+ar.data[i];
            }
            return sum;
        }
        else{std::cout<<"field dimensions don't match"<<std::endl;}
    }

    vectorField2 vectorField2::operator-(const vectorField2 &ar) {
            if (nx==ar.nx && ny==ar.ny){
                vectorField2 sum = vectorField2(nx,ny);
                for (int i=0;i<size;i++){
                    sum(i)=data[i]-ar.data[i];
                }
                return sum;
            }
            else{std::cout<<"field dimensions don't match"<<std::endl;}
        }

    vectorField2 vectorField2::operator*(const double &a){
        vectorField2 res = vectorField2(nx,ny);
        for (int i=0;i<size;i++){
        res(i)=data[i]*a;
        }
        return res;
    }

    scalarField vectorField2::magnitude(){
        scalarField mag = scalarField(nx,ny);
        for (int i=0;i<size;i++){
            mag(i)=data[i].size();
        }
        return mag;
    }

    scalarField vectorField2::xs(){
        scalarField xs = scalarField(nx,ny);
        for (int i=0;i<size;i++){
            xs(i)=data[i](0);
        }
        return xs;
    }

    scalarField vectorField2::ys(){
        scalarField ys = scalarField(nx,ny);
        for (int i=0;i<size;i++){
            ys(i)=data[i](1);
        }
        return ys;
    }