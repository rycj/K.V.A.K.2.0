#include <imgui.h>
#include <implot.h>
#include "../constants.h"
#include "iostream"
#include "../utilityFuncs.h"
#include "../calcs/FDM/FDM.h"
#include <string>

void drawFDMTab(const ImGuiViewport *viewport, ImGuiWindowFlags flags, Constants *UIConstants, FDM *fdmSolver)
{
    ImGuiWindowFlags window_flags = 0;
    ImGui::SetNextWindowPos(UIConstants->tabPos);
    ImGui::SetNextWindowSize(UIConstants->tabSize);
    ImGui::Begin("FDM", NULL, flags);
    ImGui::SetNextWindowPos(UIConstants->tabPos);

    ImGui::BeginChild("settings", UIConstants->NBodySettingsSize, ImGuiChildFlags_Borders, window_flags);

    ImGui::Text("Finite Difference Method");

    // ImGui::InputFloat("L",&odrSolver->L);
    ImGui::Combo("Equation", &fdmSolver->selectedEQ, "Heat\0String\0\0");
    ImGui::InputDouble("X", &fdmSolver->X);
    ImGui::InputDouble("T", &fdmSolver->T);
    ImGui::InputInt("nx", &fdmSolver->nx);
    ImGui::InputInt("nt", &fdmSolver->nt);
    ImGui::InputDouble("alpha", &fdmSolver->alpha);

    if (ImGui::Button("run"))
    {
        fdmSolver->runFDM();
    }

    ImGui::EndChild();
    ImGui::SameLine();
    ImGui::BeginChild("test", ImVec2(-1, -1));

    if (ImPlot::BeginPlot("fdmPlot", UIConstants->NBodyPlotSize))
    {
        ImPlot::SetupAxes("t", "x");
        // ImPlot::SetupAxesLimits(-15, 0, -20, 0);
        // ImPlot::SetNextMarkerStyle(ImPlotMarker_Circle, 4.0f);
        ImPlot::PlotLine("T", fdmSolver->xs.data(), fdmSolver->FDMMesh.getRow(fdmSolver->plotTime).data(), static_cast<int>(fdmSolver->FDMMesh.getRow(0).size()));
        // ImPlot::SetNextMarkerStyle(ImPlotMarker_Circle, 4.0f);
        // ImPlot::PlotLine("IE", odrSolver->Hlist.data(), odrSolver->IElist.data(), static_cast<int>(odrSolver->IElist.size()));

        ImPlot::EndPlot();
    }
    ImGui::SetNextItemWidth(-1.0f);
    ImGui::SliderInt("Time", &fdmSolver->plotTime, 0, fdmSolver->nt);
    ImGui::EndChild();
    ImGui::End();
}