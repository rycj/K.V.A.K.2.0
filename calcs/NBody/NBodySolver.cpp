#include "NBodySolver.h"
#include <iostream>

// double G=6.67430e-11;
double G=6.67430e-20;

vec3 NBodySolver::calcDv(int bodyI){
    vec3 dv(0,0,0);
    for (int i=0;i<bodies.size();i++){
        if (bodyI != i){
        dv=dv+((bodies[i].position.back()-bodies[bodyI].position.back())*G * bodies[bodyI].mass * bodies[i].mass)/(pow(distance(i,bodyI),3));
        }
    }
    return(dv);
}

double NBodySolver::distance(int i,int j){
		return abs(bodies[i].position.back().size()-bodies[j].position.back().size());
}

void NBodySolver::solveNBody(int end,int timeStep){
    bool setupCorrect=true;
    for (int bodyI=0;bodyI<bodies.size();bodyI++){
        if (bodies[bodyI].position.size()!=1||bodies[bodyI].velocity.size()!=1){
            std::cout<<"starting from more than 1 value in body "<<bodyI<<std::endl;
            setupCorrect=false;
        }
    }
    if(setupCorrect){
        if (end%timeStep==0){
            int Nsteps = (int)(end / timeStep);
                for (int t = 0; t < Nsteps; t++){
                    std::cout<<"precessing step "<<t<<std::endl;
                    for (int bodyI=0;bodyI<bodies.size();bodyI++){

                        bodies[bodyI].velocity.push_back((bodies[bodyI].velocity.back())+calcDv(bodyI)*timeStep);

                        bodies[bodyI].position.push_back((bodies[bodyI].position.back())+bodies[bodyI].velocity.back()*timeStep);
                    }
                }
        }
        else{
            std::cout<<"timeStep/end is not int"<<std::endl;
        }
    }
}
