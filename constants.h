#include <array>
#include <imgui.h>
#include <string>
#pragma once

// double pi = 3.141592653589;

class Constants
{
public:
    ImGuiViewport *main_viewport;
    ImVec2 mainWindowSize;
    ImVec2 tabPos;
    ImVec2 tabSize;
    ImVec2 mainStatsSize;
    ImVec2 mainStatsPos;
    ImVec2 NBodySettingsSize;
    ImVec2 FullPlotSize;
    ImVec2 NBodyPlotSize;
    ImVec2 NBodyPlotPos;
    double NBodyPosScale;
    double NBodyMassScale;

    std::array<const char *, 5> tabList;
    float mainStatsInputWidth;

    ImFont *smallFont =
        ImGui::GetIO().Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\arial.ttf", 24.0f);
    ImFont *bigFont =
        ImGui::GetIO().Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\arial.ttf", 32.0f);
    ImFont *hugeFont =
        ImGui::GetIO().Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\arial.ttf", 72.0f);
    void updateUIConstants();
};