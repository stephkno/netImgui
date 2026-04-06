// Main entry point for NetImgui Server on Linux
// This file will include all server components

// Define platform flag BEFORE any includes
#define HAL_API_PLATFORM_GLFW_GL3 1
#define IMGUI_DEFINE_MATH_OPERATORS
#define GLFW_INCLUDE_NONE

#include <GLFW/glfw3.h>

// Include all NetImguiServer components
#include "../../Code/ServerApp/Source/NetImguiServer_Config.cpp"
#include "../../Code/ServerApp/Source/NetImguiServer_Network.cpp"
#include "../../Code/ServerApp/Source/NetImguiServer_RemoteClient.cpp"
#include "../../Code/ServerApp/Source/NetImguiServer_UI.cpp"
#include "../../Code/ServerApp/Source/Custom/NetImguiServer_App_Custom.cpp"

// Include Dear ImGui core
#include "../../Code/ThirdParty/DearImgui/imgui.cpp"
#include "../../Code/ThirdParty/DearImgui/imgui_draw.cpp"
#include "../../Code/ThirdParty/DearImgui/imgui_tables.cpp"
#include "../../Code/ThirdParty/DearImgui/imgui_widgets.cpp"
#include "../../Code/ThirdParty/DearImgui/imgui_demo.cpp"

// Include NetImgui Client
#include "../../Code/Client/Private/NetImgui_Api.cpp"
#include "../../Code/Client/Private/NetImgui_Client.cpp"
#include "../../Code/Client/Private/NetImgui_CmdPackets_DrawFrame.cpp"
#include "../../Code/Client/Private/NetImgui_NetworkPosix.cpp"

// Include App_GlfwGL3 which contains main() and HAL implementations

#include "../../Code/ServerApp/Source/NetImguiServer_App.cpp"
#include "../../Code/ServerApp/Source/GlfwGL3/NetImguiServer_HAL_GL3.cpp"
#include "../../Code/ServerApp/Source/GlfwGL3/NetImguiServer_HAL_Glfw.cpp"
#include "../../Code/ServerApp/Source/GlfwGL3/NetImguiServer_App_GlfwGL3.cpp"
