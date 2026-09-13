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

vec3 NBodySolver::calcDv(int bodyI, int t){
    vec3 dv(0,0,0);
    if(bodies[bodyI].exists){
        for (int i=0;i<bodies.size();i++){
            if (bodyI != i && bodies[i].exists){
                if (distance(bodyI,i)>crashDist){
                    dv=dv+((bodies[i].position.back()-bodies[bodyI].position.back())*G * bodies[i].mass)/(pow(distance(i,bodyI),3));
                }
                else if (distance(bodyI,i)<crashDist && bodies[bodyI].exists){
                    crash(bodyI,i,t);
                }
            }
        }
    }
    else{
        dv=vec3(0,0,0);
    }

    return(dv);
}

double NBodySolver::distance(int i,int j){
		return abs((bodies[i].position.back()-bodies[j].position.back()).size());
}

void NBodySolver::crash(int i, int j, int t){
    std::cout<<"crashing bodies "<<i<<" and "<<j<<std::endl;
    double mass_new=bodies[i].mass+bodies[j].mass;
    std::cout<<"old velocities:\n"<<bodies[i].velocity.back().print(false)<<"\nand\n"<<bodies[j].velocity.back().print(false)<<std::endl;
    vec3 velocity_new=(bodies[i].velocity.back()*bodies[i].mass+bodies[j].velocity.back()*bodies[j].mass)/mass_new;
    std::cout<<"new velocity:\n"<<velocity_new.print(false);
    vec3 position_new=average3({bodies[i].position.back(),bodies[j].position.back()});
    bodies[i].exists=false;
    bodies[i].velocity.push_back(vec3(0,0,0));
    bodies[j].exists=false;
    bodies[j].velocity.push_back(vec3(0,0,0));
    std::cout<<"all is ready, pushing_back "<<bodies.size()<<" to ";
    bodies.push_back(Body(position_new,velocity_new,mass_new,ImVec4(1,0.3,0.6,1),t));
    std::cout<<bodies.size()<<std::endl;
    // bodies[j].mass=mass_new;
    // bodies[j].velocity.back()=velocity_new;
    // bodies[j].position.back()=position_new;
}

void NBodySolver::solveNBody(){
    std::cout<<"starting"<<std::endl;
    bool setupCorrect=true;
    bodies=bodies_org;
    for (int bodyI=0;bodyI<bodies.size();bodyI++){
        if (bodies[bodyI].position.size()!=1||bodies[bodyI].velocity.size()!=1){
            std::cout<<"starting from more than 1 value in body "<<bodyI<<std::endl;
            setupCorrect=false;
        }
    }
    if(setupCorrect){
        for(int i=0;i<bodies.size();i++){
            bodies[i].exists=true;
        }
        if (endTime%tStep==0){
            int Nsteps = (int)(endTime / tStep);
                for (int t = 0; t < Nsteps; t++){
                    // std::cout<<"precessing step "<<t<<std::endl;
                    for (int bodyI=0;bodyI<bodies.size();bodyI++){

                        bodies[bodyI].velocity.push_back((bodies[bodyI].velocity.back())+calcDv(bodyI,t)*tStep);

                        bodies[bodyI].position.push_back((bodies[bodyI].position.back())+bodies[bodyI].velocity.back()*tStep);
                    }
                }
        }
        else{
            std::cout<<"tStep/end is not int"<<std::endl;
        }
    }
}
