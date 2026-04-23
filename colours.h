#include <imgui.h>
#include <d3d12.h>
#include <array>
#include <string>
#pragma once
class Colours
{
public:
    ImVec4 red = (ImVec4)ImColor::HSV(0.025f, 0.95f, 0.8f);
    ImVec4 darkRed = (ImVec4)ImColor::HSV(0.0f, 0.5f, 0.5f);
    ImVec4 white = (ImVec4)ImColor::HSV(0.0f, 0.0f, 0.9f);
    ImVec4 black = (ImVec4)ImColor::HSV(0.0f, 0.0f, 0.1f);
    ImVec4 yellow = (ImVec4)ImColor::HSV(0.120f, 1.0f, 0.96f);
    ImVec4 darkYellow = (ImVec4)ImColor::HSV(0.0f, 0.0f, 0.1f);
    ImVec4 green = (ImVec4)ImColor::HSV(0.33f, 0.85f, 0.85f);
    ImVec4 blue = (ImVec4)ImColor::HSV(0.527f, 0.85f, 1.0f);
    ImVec4 purple = (ImVec4)ImColor::HSV(0.8194f, 1.0f, 1.0f);
    std::array<ImVec4, 5> menuButtonColList;
    std::array<ImVec4, 5> menuTextColList;
    ImVec4 windowBgCol;
    ImVec4 textCol;
    ImVec4 menuCol;
    ImVec4 plotAxisCol;
    void updateColours(int scheme);
};