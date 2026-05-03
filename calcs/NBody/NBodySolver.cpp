#include "NBodySolver.h"
#include <iostream>

double G=6.67430e-11;
// double G=6.67430e-20;

void Body::clear(){
    vec3 velocity_0=velocity[0];
    vec3 position_0=position[0];
    position.clear();
    velocity.clear();
    position.push_back(position_0);
    velocity.push_back(velocity_0);
}

void NBodySolver::recalcTconstants(){
    tStep=tStepHours*3600;
    endTime=endTimeDays*86400;
}

vec3 NBodySolver::calcDv(int bodyI){
    vec3 dv(0,0,0);
    for (int i=0;i<bodies.size();i++){
        if (bodyI != i){
        dv=dv+((bodies[i].position.back()-bodies[bodyI].position.back())*G * bodies[i].mass)/(pow(distance(i,bodyI),3));
        }
    }

    return(dv);
}

double NBodySolver::distance(int i,int j){
		return abs((bodies[i].position.back()-bodies[j].position.back()).size());
}

void NBodySolver::solveNBody(){
    bool setupCorrect=true;
    for (int bodyI=0;bodyI<bodies.size();bodyI++){
        if (bodies[bodyI].position.size()!=1||bodies[bodyI].velocity.size()!=1){
            std::cout<<"starting from more than 1 value in body "<<bodyI<<std::endl;
            setupCorrect=false;
        }
    }
    if(setupCorrect){
        if (endTime%tStep==0){
            int Nsteps = (int)(endTime / tStep);
                for (int t = 0; t < Nsteps; t++){
                    // std::cout<<"precessing step "<<t<<std::endl;
                    for (int bodyI=0;bodyI<bodies.size();bodyI++){

                        bodies[bodyI].velocity.push_back((bodies[bodyI].velocity.back())+calcDv(bodyI)*tStep);

                        bodies[bodyI].position.push_back((bodies[bodyI].position.back())+bodies[bodyI].velocity.back()*tStep);
                    }
                }
        }
        else{
            std::cout<<"tStep/end is not int"<<std::endl;
        }
    }
}
