#pragma once

// Minimal NetImgui Configuration for BaseExample
// Uses Dear ImGui from the repo's ThirdParty directory

#include "/home/stephen/repos/netImgui/Code/ThirdParty/DearImgui/imgui.h"
#include "/home/stephen/repos/netImgui/Code/ThirdParty/DearImgui/imgui_internal.h"

// Required for internal NetImgui functionality
#ifdef NETIMGUI_IMPLEMENTATION
    #define IMGUI_DEFINE_MATH_OPERATORS
#endif
