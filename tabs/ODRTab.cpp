#include <imgui.h>
#include <implot.h>
#include "../constants.h"
#include "iostream"
#include "../utilityFuncs.h"
#include "../calcs/ODR/odr.h"
#include <string>



void drawODRTab(const ImGuiViewport *viewport, ImGuiWindowFlags flags, Constants* UIConstants,ODR* odrSolver)
{
    ImGuiWindowFlags window_flags = 0;
    ImGui::SetNextWindowPos(UIConstants->tabPos);
    ImGui::SetNextWindowSize(UIConstants->tabSize);
    ImGui::Begin("ODR", NULL, flags);
        ImGui::SetNextWindowPos(UIConstants->tabPos);

        ImGui::BeginChild("settings", UIConstants->NBodySettingsSize, ImGuiChildFlags_Borders, window_flags);

            ImGui::Text("ODR");

            // ImGui::InputFloat("L",&odrSolver->L);
            ImGui::InputInt("N steps",&odrSolver->N);
            ImGui::Text("largest number of steps (1/smallest timestep)");
            if (ImGui::Button("run"))
            {
                odrSolver->clear();
                odrSolver->runODR();
            }

        ImGui::EndChild();
        ImGui::SameLine();
        ImGui::BeginChild("test",ImVec2(-1,-1));

        if (ImPlot::BeginPlot("odrPlot",UIConstants->FullPlotSize)) {
            ImPlot::SetupAxes("log(∆t)","log(Error)");
            ImPlot::SetupAxesLimits(-15, 0, -20, 0);
            ImPlot::SetNextMarkerStyle(ImPlotMarker_Circle, 4.0f);
            ImPlot::PlotLine("E", odrSolver->Hlist.data(), odrSolver->Elist.data(), static_cast<int>(odrSolver->Elist.size()));
            ImPlot::SetNextMarkerStyle(ImPlotMarker_Circle, 4.0f);
            ImPlot::PlotLine("IE", odrSolver->Hlist.data(), odrSolver->IElist.data(), static_cast<int>(odrSolver->IElist.size()));

            ImPlot::EndPlot();
        }
        ImGui::EndChild();
    ImGui::End();
}