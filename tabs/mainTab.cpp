#include <imgui.h>
#include <implot.h>
#include "../constants.h"
#include "iostream"
#include "../utilityFuncs.h"
#include "../calcs/NBody/NBodySolver.h"
#include <string>
#include <cmath>

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
            ImGui::BeginChild(std::to_string(bodyI).c_str(),ImVec2(UIConstants->NBodySettingsSize[0]*9/10,UIConstants->NBodySettingsSize[1]/8));
                
                ImGui::Text(("body "+std::to_string(bodyI)).c_str());
            
                InputDouble3("position",solver->bodies_org[bodyI].position[0].arr.data());

                InputDouble3("velocity",solver->bodies_org[bodyI].velocity[0].arr.data());

                ImGui::InputDouble("mass",&solver->bodies_org[bodyI].mass);

                ImGui::ColorEdit4("Color", &solver->bodies_org[bodyI].colour.x);

                if (ImGui::Button("delete"))
                {
                    solver->bodies_org.erase(solver->bodies_org.begin()+bodyI);
                }

            ImGui::EndChild();
        }

            ImGui::SliderInt("end time (d)", &solver->endTimeDays, 1, 10000);
            ImGui::SliderInt("time step (h)", &solver->tStepHours, 1, 24);
            ImGui::Text("Load preset:");
            if (ImGui::Button("stable"))
            {   
                solver->bodies_org.push_back(Body(vec3(-7.42933254e8f,0.0f,0.0f),vec3(0.0f,-12.5584f,0.0f),1.98847e30f,ImVec4(1,0.824,0,1)));
                solver->bodies_org.push_back(Body(vec3(1.48854937e11f,0.0f,0.0f),vec3(0.0f,29772.63f,0.0f),5.9722e24f,ImVec4(0,0.7647,0.2235,1)));
                solver->bodies_org.push_back(Body(vec3(7.77824225e11f,0.0f,0.0f),vec3(0.0f,13049.80f,0.0f),1.89813e27f,ImVec4(0.6,0.6,0.6,1)));
            }
            ImGui::SameLine();
            if (ImGui::Button("unstable"))
            {   
                solver->bodies_org.push_back(Body(vec3(-1.60e11f,0.0e0f,0.0f),vec3(0.0e0f,-1.5e4f,0.0e0f),1.0e30f,ImVec4(1,0.824,0,1)));
                solver->bodies_org.push_back(Body(vec3(0.80e11f,1.10e11f,0.0e0f),vec3(-1.55e4f,1.05e4f,0.0e0f),7.0e29f,ImVec4(0,0.7647,0.2235,1)));
                solver->bodies_org.push_back(Body(vec3(1.10e11f,-1.00e11f,0.0e0f),vec3(1.65e4f,1.00e4f,0.0e0f),5.0e29f,ImVec4(0.6,0.6,0.6,1)));
                solver->endTimeDays=3650;
            }
            ImGui::SameLine();
            if (ImGui::Button("gravity assist"))
            {   
                solver->bodies_org.push_back(Body(vec3(0.0e0f,0.0e0f,0.0e0f),vec3(0.0e0f,0.0e0f,0.0e0f),1.98847e30f,ImVec4(1,0.824,0,1)));
                solver->bodies_org.push_back(Body(vec3(7.785e11f,0.0e0f,0.0e0f),vec3(0.0e0f,1.3078e4f,0.0e0f),1.89813e27f,ImVec4(0,0.7647,0.2235,1)));
                solver->bodies_org.push_back(Body(vec3(6.00e11f,1.40e9f,0.0e0f),vec3(5.00e3f,8.00e3f,0.0e0f),1.0e3f,ImVec4(0.6,0.6,0.6,1)));
                solver->endTimeDays=3650;
            }
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
        ImGui::BeginChild("plotWindow",ImVec2(-1,-1));
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
                                ImPlot::SetNextLineStyle(solver->bodies[BodyI].colour);
                                ImPlot::PlotLine("NBodyPlot",xs.data(),ys.data(),solver->plotIter);
                                // Draw ball at current/tip position
                                double tipX = xs.back();
                                double tipY = ys.back();

                                ImPlot::SetNextMarkerStyle(
                                    ImPlotMarker_Circle,
                                    std::log10(solver->bodies[BodyI].mass)/3,
                                    solver->bodies[BodyI].colour
                                );

                                ImPlot::PlotScatter(
                                    "Body",
                                    &tipX,
                                    &tipY,
                                    1
                                );
                                // std::cout<<"plot time"<<solver->plotIter<<std::endl;
                            }
                            solver->plotIter+=10;
                        }
                    }
                ImPlot::EndPlot();
                
            }
            ImGui::SetNextItemWidth(-1.0f);
            ImGui::SliderInt("simTime",&solver->plotIter,0,solver->endTime/solver->tStep);
            
        ImGui::EndChild();
        
    ImGui::End();
}