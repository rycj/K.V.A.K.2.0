#include "odr.h"
// #include <cmath>
#include <vector>

float ODR::Eulerror(float h_local, int N){
    float y_anal = exp(-5 * L);
    float y = 1;
    for (int t=0;t<int(N);t++){
        y = y + h_local * f(y);
    }
    return abs(y - y_anal);
}

float ODR::ImprovedEulerror(float h_local, int N){
    float y_anal = exp(-5 * L);
    float y = 1;
    for (int t=0;t<int(N);t++){
        y = y + h_local * (0.5 * f(y) + 0.5 * f(y + h_local * f(y)));
    }
    return abs(y - y_anal);
}

float ODR::f(float x){
    return -5 * x;
}
void ODR::clear(){
Elist.clear();
IElist.clear();
Hlist.clear();
}

void ODR::runODR(){
    while (N>1){
        float h_local=L/N;
        Elist.push_back(log10(Eulerror(h_local,N)));
        IElist.push_back(log10(ImprovedEulerror(h_local,N)));
        Hlist.push_back(log10(h_local));
        N*=0.9;
    }
}