#include <imgui.h>
#include "../constants.h"
#include "vector"
#include "../calcs/NBody/NBodySolver.h"
#pragma once

void drawMainTab(const ImGuiViewport *viewport, ImGuiWindowFlags flags, Constants* UIConstants, NBodySolver* solver);