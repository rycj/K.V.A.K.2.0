#include <imgui.h>
#include <d3d12.h>
#include "colours.h"

void Colours::updateColours(int scheme)
{
    menuButtonColList = {red,
                         yellow,
                         green,
                         blue,
                         purple};
    menuTextColList = {white,
                         black,
                         black,
                         black,
                         white};
    if (scheme == 0)
    {
        windowBgCol = white;
        plotAxisCol = white;
        textCol = black;
        menuCol = red;
    }
    else if (scheme == 1)
    {
        windowBgCol = white;
        plotAxisCol = white;
        textCol = black;
        menuCol = yellow;
    }
    else if (scheme == 2)
    {
        windowBgCol = white;
        plotAxisCol = white;
        textCol = black;
        menuCol = green;
    }
    else if (scheme == 3)
    {
        windowBgCol = white;
        plotAxisCol = white;
        textCol = black;
        menuCol = blue;
    }
    else if (scheme == 4)
    {
        windowBgCol = white;
        plotAxisCol = white;
        textCol = black;
        menuCol = purple;
    }
}