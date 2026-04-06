#pragma once

// Minimal NetImgui Server Configuration for Linux Build
// Uses Dear ImGui and NetImgui from the repo

#include "../Code/ThirdParty/DearImgui/imgui.h"
#include "../Code/ThirdParty/DearImgui/imgui_internal.h"

// Required for internal NetImgui functionality
#ifdef NETIMGUI_IMPLEMENTATION
    #define IMGUI_DEFINE_MATH_OPERATORS
#endif
