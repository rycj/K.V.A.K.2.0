#include <imgui.h>
#include "../constants.h"
#include "../calcs/ODR/odr.h"
#pragma once

void drawODRTab(const ImGuiViewport *viewport, ImGuiWindowFlags flags, Constants* UIConstants,ODR* odrSolver);