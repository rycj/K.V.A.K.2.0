#include <imgui.h>
#include "constants.h"
void Constants::updateUIConstants()
{
    main_viewport = ImGui::GetMainViewport();
    mainWindowSize = main_viewport->Size;
    tabPos = ImVec2(main_viewport->WorkPos.x, ((main_viewport->WorkPos.y) + (mainWindowSize[1] / 20)));
    tabSize = ImVec2(mainWindowSize[0], mainWindowSize[0] / 10 * 9);
    tabList = {"Main", "2", "3", "4", "5"};
    NBodySettingsSize = ImVec2(mainWindowSize.x / 5, mainWindowSize.y);
    NBodyPlotSize=ImVec2(mainWindowSize.x *4/ 5, mainWindowSize.y*19/20);
    double NBodyPosScale=149597870700;
    double NBodyMassScale=2e30;
}