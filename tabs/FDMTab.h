#include <imgui.h>
#include "../constants.h"
#include "../calcs/FDM/FDM.h"
#pragma once

void drawFDMTab(const ImGuiViewport *viewport, ImGuiWindowFlags flags, Constants *UIConstants, FDM *fdmSolver);