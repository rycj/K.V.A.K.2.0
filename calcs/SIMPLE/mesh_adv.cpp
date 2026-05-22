#include "mesh.h"
#include <cmath>
vertice::vertice(double x_,double y_, int id_){
    x=x_;
    y-y_;
    id=id_;
}

CartMesh2d::CartMesh2d(int x_, int y_, int nx_, int ny_){
    for (int i=0;i<(nx_+1);i++){
        for (int j=0;j<(ny_+1);j++){
            vertices.push_back(vertice(i*x_/nx_,j*y_/ny_,j+i*(ny_+1)));
        }
    }
    for (int i=0;i<(nx_);i++){
        for (int j=0;j<(ny_);j++){
            cells.push_back(cell(this,nx_*ny_,{j+i*(ny_),j+(i+1)*(ny_),(ny_*(nx_+1))+j*(nx_)+i,(ny_*(nx_+1))+(j+1)*(nx_)+i},j+i*(ny_)));
        }
    }
}

face::face(CartMesh2d* mesh_, bool B,double size_,int id_,std::string BType){
    mesh=mesh_;
    boundary=B;
    boundaryType=BType;
    size=size_;
    id=id_;
}

cell::cell(CartMesh2d* mesh_, double area_, std::array<int,4> faceIDs,int id_){
    
}