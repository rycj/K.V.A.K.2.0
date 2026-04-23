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
            cells.push_back(cell())
        }
    }
}