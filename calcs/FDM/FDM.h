#include <vector>
#include "../../dataStructs/scalarField.h"
#pragma once
class FDM
{
public:
    scalarField FDMMesh = scalarField(nx + 2, nt + 1);
    std::vector<double> xs;
    int plotTime = 0;
    int nx = 100;
    int nt = 10000;
    double X = 1.0;
    double T = 1.0;
    void solveHeatEQ(std::string IC, std::string BCType, double BCLeft, double BCRight);
    void solveStringEQ();
    double alpha = 0.5;
};