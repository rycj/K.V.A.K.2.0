#include <vector>
#include <array>
#include "../../utilityFuncs.h"
#pragma once
class Body{
    public:
        double mass;
        std::vector<vec3> position;
        std::vector<vec3> velocity;

        Body(vec3 pos,vec3 vel,double m){
            position.push_back(pos);
            velocity.push_back(vel);
            mass=m;
        };
        void clear();
};

class NBodySolver{
    public:
    std::vector<Body> bodies;
    int plotIter=0;
    int endTimeDays=365;
    int tStepHours=1;
    int endTime;
    int tStep;
    void NBodySolver::recalcTconstants();
    vec3 NBodySolver::calcDv(int bodyI);
    double NBodySolver::distance(int i,int j);
    void NBodySolver::solveNBody();
};