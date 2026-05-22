#include "Simple.h"
#include <iostream>
vectorField2 GaussSeidel(scalarField A, vectorField2 b){
    if(A.nx==b.size){
        float diff;
        vec2 sum=vec2(0,0);

        vectorField2 x = vectorField2(b.nx,b.ny);
        do {
            diff=0;
            for (int i=0;i<A.ny;i++){
                sum=vec2(0,0);
                for (int j=0;j<A.nx;j++){
                    if (i!=j){
                        sum=sum+x(j)*A(i,j);
                    }
                }
                diff+=abs(((b(i)-sum)/A(i,i)-x(i)).size());
                x(i)=(b(i)-sum)/A(i,i);
            }
        }
        while (diff>1e-5);
        return x;
    }
    else{
        std::cerr<<"fuck you"<<std::endl;
    }
}


scalarField AssembleCoefficientMatrix(mesh m, double mu){
    scalarField A = scalarField(m.size,m.size);
    double k = mu/pow(m.h,2);
    for (int i = 0; i < m.size; i ++){
        for (int side;side<m.sides.size();side++){
            int j=(m.*m.sides[side])(i);
            if (j!=-1){
                A(i,j)=-k;
                A(i,i)+=k;
            }
            else{
                A(i,i)+=2*k;
            }
        }
    }
    return (A);
}

vectorField2 AssembleRightSide(mesh m, double mu){
    vectorField2 b = vectorField2(m.nx,m.ny);
    double k = mu/pow(m.h,2);
    for (int i = 0; i < m.size; i ++){
        for (int side=0;side<m.sides.size();side++){
            int j=(m.*m.sides[side])(i);
            if (j==-1){
                b(i)=b(i)-(*m.BCs[side]*2*k);
            }
        }
    }
    return (b);
}

vectorField2 ComputePressureGradient(mesh m){
    vectorField2 gradp = vectorField2(m.nx,m.ny);
    for (int i=0;i<m.size;i++){
        gradp(i)=vec2((m.p(m.east(i))-m.p(m.west(i)))/2,(m.p(m.north(i))-m.p(m.south(i)))/2);
    }
}

void SolveVelocityField(mesh m, double mu){
    scalarField A = AssembleCoefficientMatrix(m,mu);
    vectorField2 b = vectorField2(m.nx,m.ny) - ComputePressureGradient(m) - AssembleRightSide(m,mu);
    m.u=GaussSeidel(A,b);
}


int mesh::east(int i){
    if (i%nx==-1){
        return -1;
    }
    return i+1;
}

int mesh::west(int i){
    if (i%nx==0){
        return -1;
    }
    return i-1;
}

int mesh::north(int i){
    if (i>=nx*(ny-1)){
        return -1;
    }
    return i+nx;
}

int mesh::south(int i){
    if (i<nx){
        return -1;
    }
    return i-nx;
}

int mesh::boundaryN(int i){ 
    int n=0;
    if (i<nx || i>=nx*(ny-1)){
        n+=1;
    }
    if (i%nx==-1 || i%nx==0){
        n+=1;
    }
    return n;
}