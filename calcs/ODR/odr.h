#include <vector>
#pragma once
class ODR{
    public:
        float L=1;
        int N=1e7;
        float h;
        float Eulerror(float h_local, int N);
        float ImprovedEulerror(float h_local, int N);
        float f(float x);
        void runODR();
        void clear();
        std::vector<float> Elist;
        std::vector<float> IElist;
        std::vector<float> Hlist;
};