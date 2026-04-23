#include "utilityFuncs.h"
#include <cmath>
#include <array>
#include <vector>
#include <imgui.h>
#include <cstring>
#include "iostream"
#include "string"

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

    double vec3::size(){
        double size=0;
        for (int i = 0; i < 3; i++)
		{
			size+=pow(arr[i],2);
		}
        size=sqrt(size);
        return(size);
    }

std::string intToSignedString(int i) {
        std::string str;
        if (i>0){
            str="+"+std::to_string(i);
        }
        else str=std::to_string(i);
        return(str);
    
}
std::vector<double> getColumn(std::vector<vec3> data, int i, double scale){
    if (-1<i && i<3){
        std::vector<double> col;
        for (int j=0;j<data.size();j++){
            col.push_back(data[j].arr[i]*scale);
        }
        return (col);
    }
    else{
        std::cout<<"please enter a valid vec3 index for getColumn"<<std::endl;
    }
}

bool InputDouble3(const char* label, double v[3])
{
    return ImGui::InputScalarN(label, ImGuiDataType_Double, v, 3);
}
