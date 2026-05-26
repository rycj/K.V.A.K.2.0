#include "utilityFuncs.h"
#include <cmath>
#include <array>
#include <vector>
#include <imgui.h>
#include <cstring>
#include "iostream"
#include "string"


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

std::vector<double> getColumn(std::vector<vec2> data, int i, double scale){
    if (-1<i && i<2){
        std::vector<double> col;
        for (int j=0;j<data.size();j++){
            col.push_back(data[j].arr[i]*scale);
        }
        return (col);
    }
    else{
        std::cout<<"please enter a valid vec2 index for getColumn"<<std::endl;
    }
}

bool InputDouble3(const char* label, double v[3])
{
    return ImGui::InputScalarN(label, ImGuiDataType_Double, v, 3);
}
