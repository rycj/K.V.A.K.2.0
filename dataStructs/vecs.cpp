#include "string"
#include "vecs.h"
#include <array>
#include <vector>
#include <iostream>
    vec3::vec3(double i,double j,double k){
        arr={i,j,k};
    }
         
    vec3::vec3(double i[3]){
            arr={i[0],i[1],i[2]};
         };

    vec3 vec3::operator+(const vec3 &ar){
        return(vec3(arr[0]+ar.arr[0],arr[1]+ar.arr[1],arr[2]+ar.arr[2]));
    }

    vec3 vec3::operator-(const vec3 &ar){
        return(vec3(arr[0]-ar.arr[0],arr[1]-ar.arr[1],arr[2]-ar.arr[2]));
    }

    vec3 vec3::operator*(const double &f){
        return(vec3(arr[0]*f,arr[1]*f,arr[2]*f));
    }

    vec3 vec3::operator/(const double &f){
        return(vec3(arr[0]/f,arr[1]/f,arr[2]/f));
    }

    std::string vec3::print(bool out){
        std::string a = std::to_string(arr[0]) + ";" + std::to_string(arr[1]) + ";" + std::to_string(arr[2]);
        if(out){
            std::cout<<a<<std::endl;
        }
        return (a);
    }

    double vec3::size(){
        double size=0;
        for (int i = 0; i < 3; i++)
		{
			size+=pow(arr[i],2);
		}
        size=sqrt(size);
        return(size);
    }

    vec3 average3(std::vector<vec3> vecs){
        vec3 sum= vec3(0,0,0);
        for (int i=0;i<vecs.size();i++){
            sum=sum+vecs[i];
        }
        return (sum/vecs.size());
    }


    vec2::vec2(double i,double j){
        arr={i,j};
    }
         
    vec2::vec2(double i[2]){
            arr={i[0],i[1]};
         };

    vec2 vec2::operator+(const vec2 &ar){
        return(vec2(arr[0]+ar.arr[0],arr[1]+ar.arr[1]));
    }

    vec2 vec2::operator-(const vec2 &ar){
        return(vec2(arr[0]-ar.arr[0],arr[1]-ar.arr[1]));
    }

    vec2 vec2::operator*(const double &f){
        return(vec2(arr[0]*f,arr[1]*f));
    }

    vec2 vec2::operator*(const double &f) const{
        return(vec2(arr[0]*f,arr[1]*f));
    }

    vec2 vec2::operator/(const double &f){
        return(vec2(arr[0]/f,arr[1]/f));
    }
    double vec2::operator()(const int i){
        return arr[i];
    }

    std::string vec2::print(bool out){
        std::string a = std::to_string(arr[0]) + ";" + std::to_string(arr[1]);
        if(out){
            std::cout<<a<<std::endl;
        }
        return (a);
    }

    double vec2::size(){
        double size=0;
        for (int i = 0; i < 2; i++)
		{
			size+=pow(arr[i],2);
		}
        size=sqrt(size);
        return(size);
    }