#include <imgui.h>
#include <implot.h>
#include "../constants.h"
#include "iostream"
#include "../utilityFuncs.h"
#include "../calcs/NBody/NBodySolver.h"
#include <string>

bool plot;

void drawMainTab(const ImGuiViewport *viewport, ImGuiWindowFlags flags, Constants* UIConstants, NBodySolver* solver)
{
    ImGuiWindowFlags window_flags = 0;
    ImGui::SetNextWindowPos(UIConstants->tabPos);
    ImGui::SetNextWindowSize(UIConstants->tabSize);
    ImGui::Begin("NBody", NULL, flags);

        ImGui::SetNextWindowPos(UIConstants->tabPos);

        ImGui::BeginChild("settings", UIConstants->NBodySettingsSize, ImGuiChildFlags_Borders, window_flags);
        if (ImGui::Button("new Body"))
                {
                    solver->bodies_org.push_back(Body(vec3(0.0f,0.0f,0.0f),vec3(0.0f,0.0f,0.0f),0.0f));
                }
        for (int bodyI=0;bodyI<solver->bodies_org.size();bodyI++){
            ImGui::BeginChild(std::to_string(bodyI).c_str(),ImVec2(UIConstants->NBodySettingsSize[0]*9/10,UIConstants->NBodySettingsSize[1]/10));
                
                ImGui::Text(("body "+std::to_string(bodyI)).c_str());
            
                InputDouble3("position",solver->bodies_org[bodyI].position[0].arr.data());

                InputDouble3("velocity",solver->bodies_org[bodyI].velocity[0].arr.data());

                ImGui::InputDouble("mass",&solver->bodies_org[bodyI].mass);

            ImGui::EndChild();
        }

            ImGui::SliderInt("end time (d)", &solver->endTimeDays, 1, 3650);
            ImGui::SliderInt("time step (h)", &solver->tStepHours, 1, 24);
            solver->recalcTconstants();

        if (ImGui::Button("START"))
        {   
            for (int i=0;i<solver->bodies_org.size();i++)
            {
                solver->bodies_org[i].clear();
            }
            solver->solveNBody();
            // double topSize = 0;
            // for (int i=0;i<solver->bodies[1].velocity.size();i++)
            // {
                
            //     if (solver->bodies[1].velocity[i].size()>topSize)
            //     {
                    
            //         topSize=solver->bodies[1].velocity[i].size();
            //     }
            // }
            // std::cout<<topSize<<"\n";
            
        }
        if (ImGui::Button("plot"))
        {
            solver->plotIter=1;
            plot=true;
            // for (int i=0;i<solver->bodies[2].position.size();i++){
            //     std::cout<<solver->bodies[2].position[i].arr[0]<<";"<<solver->bodies[2].position[i].arr[1]<<"\n";
            // }
        }
        ImGui::EndChild();
        ImGui::SameLine();
        ImGui::BeginChild("test",ImVec2(-1,-1));
            // ImGui::SetNextWindowPos(UIConstants->NBodyPlotPos);

            if (ImPlot::BeginPlot("My Plot",UIConstants->NBodyPlotSize)) {
                    ImPlot::SetupAxes("X", "Y");
                    ImPlot::SetupAxesLimits(-150e9, 150e9,-150e9, 150e9);
                    if (plot==true){
                        if (solver->plotIter<solver->bodies[0].position.size() && solver->plotIter!=0){
                            for (int BodyI=0;BodyI<solver->bodies.size();BodyI++){
                                std::vector<double> fullX=getColumn(solver->bodies[BodyI].position,0, 1);
                                std::vector<double> fullY=getColumn(solver->bodies[BodyI].position,1, 1);
                                std::vector<double> fullZ=getColumn(solver->bodies[BodyI].position,2, 1);
                                std::vector<double> xs(fullX.begin(),fullX.begin()+solver->plotIter);
                                std::vector<double> ys(fullY.begin(),fullY.begin()+solver->plotIter);
                                ImPlot::PlotLine("NBodyPlot",xs.data(),ys.data(),solver->plotIter);
                                // std::cout<<"plot time"<<solver->plotIter<<std::endl;
                            }
                            solver->plotIter+=10;
                        }
                    }
                ImPlot::EndPlot();

            }
        ImGui::EndChild();
        
    ImGui::End();
}