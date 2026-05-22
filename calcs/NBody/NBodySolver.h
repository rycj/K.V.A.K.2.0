#include <vector>
#include <array>
#include "../../utilityFuncs.h"
#pragma once
class Body{
    public:
        double mass;
        bool exists=true;
        std::vector<vec3> position;
        std::vector<vec3> velocity;

        Body(vec3 pos,vec3 vel,double m,int t=1){
            for (int i=0;i<t;i++){
                position.push_back(pos);
                velocity.push_back(vel);
        }
            mass=m;
        };
        void clear();
};

class NBodySolver{
    public:
    std::vector<Body> bodies;
    std::vector<Body> bodies_org;
    // int crashDist = 6378000*2;
    int crashDist = 1e7;
    int plotIter=0;
    int endTimeDays=365;
    int tStepHours=1;
    int endTime;
    int tStep;
    void NBodySolver::recalcTconstants();
    vec3 NBodySolver::calcDv(int bodyI,int t);
    double NBodySolver::distance(int i,int j);
    void NBodySolver::crash(int i, int j, int t);
    void NBodySolver::solveNBody();
};