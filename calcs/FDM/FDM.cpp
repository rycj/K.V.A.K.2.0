#include "FDM.h"
#include "../../constants.h"
#include <cmath>
#include <iostream>

void FDM::solveHeatEQ(std::string IC, std::string BCType, double BCLeft, double BCRight)
{
    double dx = X / (nx - 1);
    double dt = T / (nt - 1);
    FDMMesh = scalarField(nx, nt + 1);
    xs.clear();

    // apply IE
    if (IC == "sin")
    {
        for (int i = 0; i < nx; i++)
        {
            FDMMesh(i, 0) = 3 * sin((i * dx) * 3.141592653589);
            xs.push_back(i * dx);
        }
    }
    else
    {
        for (int i = 0; i < nx; i++)
        {
            FDMMesh(i, 0) = 20;
            xs.push_back(i * dx);
        }
    }

    // apply BCs
    for (int j = 0; j <= nt; j++)
    {
        if (BCType == "Dirichlet")
        {
            FDMMesh(0, j) = BCLeft;
            FDMMesh(nx - 1, j) = BCRight;
        }
    };

    // main loop
    for (int j = 1; j <= nt; j++)
    {
        for (int i = 1; i < nx - 1; i++)
        {
            // std::cout << "\ni: " << i << "\nj: " << j << "\nu(i-1,j-1): " << FDMMesh(i - 1, j - 1) << "\nu(i,j-1): " << FDMMesh(i, j - 1) << "\nu(i+1,j-1): " << FDMMesh(i + 1, j - 1);
            FDMMesh(i, j) = FDMMesh(i, j - 1) + pow(alpha, 2) * (FDMMesh(i - 1, j - 1) - 2 * FDMMesh(i, j - 1) + FDMMesh(i + 1, j - 1)) / (pow(dx, 2) / dt);
            // std::cout << "\nu(i,j)" << FDMMesh(i, j) << std::endl;
        }
    }
    // FDMMesh.printGrid(2);
}

void FDM::solveStringEQ(std::string IC, std::string BCType, double BCLeft, double BCRight)
{
    double dx = X / (nx - 1);
    double dt = T / (nt - 1);
    FDMMesh = scalarField(nx, nt + 1);
    xs.clear();

    // apply IE
    if (IC == "sin")
    {
        for (int i = 0; i < nx; i++)
        {
            FDMMesh(i, 0) = 3 * sin((i * dx) * 3.141592653589);
            xs.push_back(i * dx);
        }
    }
    else
    {
        for (int i = 0; i < nx; i++)
        {
            FDMMesh(i, 0) = 20;
            xs.push_back(i * dx);
        }
    }

    // apply BCs
    for (int j = 0; j <= nt; j++)
    {
        if (BCType == "Dirichlet")
        {
            FDMMesh(0, j) = BCLeft;
            FDMMesh(nx - 1, j) = BCRight;
        }
    };

    // main loop
    for (int j = 1; j <= nt; j++)
    {
        for (int i = 1; i < nx - 1; i++)
        {
            // std::cout << "\ni: " << i << "\nj: " << j << "\nu(i-1,j-1): " << FDMMesh(i - 1, j - 1) << "\nu(i,j-1): " << FDMMesh(i, j - 1) << "\nu(i+1,j-1): " << FDMMesh(i + 1, j - 1);
            // FDMMesh(i, j) = FDMMesh(i, j - 1) + pow(alpha, 2) * (FDMMesh(i - 1, j - 1) - 2 * FDMMesh(i, j - 1) + FDMMesh(i + 1, j - 1)) / (pow(dx, 2) / dt);
            // std::cout << "\nu(i,j)" << FDMMesh(i, j) << std::endl;
        }
    }
    // FDMMesh.printGrid(2);
}