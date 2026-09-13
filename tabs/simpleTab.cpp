#include <imgui.h>
#include <implot.h>
#include "../constants.h"
#include "iostream"
#include "../utilityFuncs.h"
#include "../calcs/SIMPLE/Simple.h"
#include <string>
#include <algorithm>

void drawSimpleTab(const ImGuiViewport *viewport, ImGuiWindowFlags flags, Constants* UIConstants, mesh* m)
{
    ImGuiWindowFlags window_flags = 0;
    ImGui::SetNextWindowPos(UIConstants->tabPos);
    ImGui::SetNextWindowSize(UIConstants->tabSize);
    ImGui::Begin("NBody", NULL, flags);

        ImGui::SetNextWindowPos(UIConstants->tabPos);

        ImGui::BeginChild("settings", UIConstants->NBodySettingsSize, ImGuiChildFlags_Borders, window_flags);

        ImGui::Text("SIMPLE");

        ImGui::InputInt("Nx",&m->nx);
        ImGui::InputInt("Ny",&m->ny);
        ImGui::InputFloat("L",&m->Lx);

        if (ImGui::Button("Update Mesh"))
                {
                    m->update();
                }

        ImGui::Text(std::to_string((m->h)).c_str());

        if (ImGui::Button("RUN"))
        {
            SIMPLE(m);
        }
        if (ImGui::Button("print p"))
        {
            m->p.printGrid();
        }
        if (ImGui::Button("print u"))
        {
            m->u.magnitude().printGrid();
        }
        if (ImGui::Button("test"))
        {
            m->u.magnitude().printGrid();
        }

        ImGui::EndChild();
        ImGui::SameLine();
        ImGui::BeginChild("test",ImVec2(-1,-1));
            // ImGui::SetNextWindowPos(UIConstants->NBodyPlotPos);
        if (ImPlot::BeginPlot("Pressure",UIConstants->NBodyPlotSize)) {
            ImPlot::SetupAxesLimits(0, m->Lx, 0, m->Ly, ImGuiCond_Always);
            double pMin = *std::min_element(m->p.data.begin(), m->p.data.end());
            double pMax = *std::max_element(m->p.data.begin(), m->p.data.end());

            ImPlot::PlotHeatmap(
                "p",
                m->u.magnitude().data.data(),
                // m->p.data.data(),
                m->ny,   // rows
                m->nx,   // cols
                pMin,
                pMax,
                nullptr,
                ImPlotPoint(0, 0),
                ImPlotPoint(m->Lx, m->Ly)
            );

            ImPlot::EndPlot();
        }

            
        ImGui::EndChild();





    ImGui::End();


}