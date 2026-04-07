//=================================================================================================
// NETIMGUI BASE EXAMPLE
//-------------------------------------------------------------------------------------------------
// Minimal standalone example demonstrating NetImgui client setup.
// 
// This example:
// - Initializes Dear ImGui with no rendering backend (headless)
// - Connects to a NetImgui Server for remote display
// - Provides a simple UI that can be controlled remotely
//
// Build instructions:
//   make                    # Build with Makefile
//   ./build.sh              # Build with build script (legacy)
//
// Usage:
//   1. Start the NetImgui Server application first
//   2. Run this example
//   3. Connect via the UI menu or it will auto-connect to localhost:54108
//=================================================================================================

#define NETIMGUI_IMPLEMENTATION
#include <NetImgui_Api.h>

#include <cstdio>
#include <thread>
#include <chrono>

//-------------------------------------------------------------------------------------------------
// Application State
//-------------------------------------------------------------------------------------------------
struct AppSettings
{
    float   sliderValue   = 0.5f;
    bool    checkboxValue = true;
    char    textBuffer[128] = "Hello, NetImgui!";
    int     counter       = 0;
};

static AppSettings g_Settings;
static bool        g_IsConnected  = false;
static bool        g_Quit         = false;

//-------------------------------------------------------------------------------------------------
// Startup: Initialize Dear ImGui and NetImgui
//-------------------------------------------------------------------------------------------------
bool App_Startup()
{
    printf("================================================================================\n");
    printf("  NetImgui Base Example\n");
    printf("================================================================================\n");
    printf("  Dear ImGui Version: %s\n", IMGUI_VERSION);
    printf("  NetImgui Version:   %s\n", NETIMGUI_VERSION);
    printf("\n");
   printf("  Instructions:\n");
      printf("    1. Start the NetImgui Server application\n");
      printf("    2. Server will connect to this client on port %d\n", NetImgui::kDefaultClientPort);
      printf("    3. This client listens for any server connection\n");
      printf("\n");
    printf("--------------------------------------------------------------------------------\n");

    // Initialize Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    
    ImGuiIO& io = ImGui::GetIO();
    io.BackendFlags |= ImGuiBackendFlags_HasGamepad;  // Enable gamepad support
    
    // Set default display size (required before first NewFrame call)
    io.DisplaySize = ImVec2(1280, 720);
    
    // Setup basic style
    ImGui::StyleColorsDark();
    
    // Add a font (using default for now)
    // For custom fonts, you would load them here before NetImgui::Startup()
    
    // Initialize NetImgui library
    if (!NetImgui::Startup())
    {
        fprintf(stderr, "ERROR: Failed to initialize NetImgui\n");
        return false;
    }

    printf("Initialization complete. Waiting for connection...\n");
    return true;
}

//-------------------------------------------------------------------------------------------------
// Shutdown: Cleanup resources
//-------------------------------------------------------------------------------------------------
void App_Shutdown()
{
    printf("\nShutting down...\n");
    
    NetImgui::Shutdown();
    ImGui::DestroyContext();
    
    printf("Cleanup complete.\n");
}

//-------------------------------------------------------------------------------------------------
// Connection Management
//-------------------------------------------------------------------------------------------------
void App_UpdateConnection()
{
    static bool s_AttemptedConnect = false;
    
    // Check connection status
    bool wasConnected = g_IsConnected;
    g_IsConnected = NetImgui::IsConnected();
    
    // Handle status changes
    if (g_IsConnected && !wasConnected)
    {
        printf(">>> CONNECTED to NetImgui Server\n");
    }
    else if (!g_IsConnected && wasConnected)
    {
        printf("<<< DISCONNECTED from NetImgui Server\n");
        s_AttemptedConnect = false;  // Allow reconnection attempt
    }
    
    // Auto-connect on first run
     if (!s_AttemptedConnect && !g_IsConnected && !NetImgui::IsConnectionPending())
     {
         s_AttemptedConnect = true;
         printf("Listening for server connection on port %d...\n", NetImgui::kDefaultClientPort);
        
        // Listen for server-to-client connections (accept any server IP)
        NetImgui::ConnectFromApp("BaseExample");
    }
}

//-------------------------------------------------------------------------------------------------
// Drawing: Render ImGui UI
//-------------------------------------------------------------------------------------------------
void App_Draw()
{
    // Check if we should draw this frame
    // NetImgui::NewFrame(true) enables frame skipping for efficiency
    if (!NetImgui::NewFrame(true))
    {
        return;  // Skip this frame
    }

    // Main menu bar with connection info
    if (ImGui::BeginMainMenuBar())
    {
        ImGui::Text("BaseExample");
        ImGui::SameLine();
        
        if (g_IsConnected)
        {
            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.2f, 1.0f, 0.2f, 1.0f));
            ImGui::Text("● Connected");
            ImGui::PopStyleColor();
            
            if (ImGui::Button("Disconnect"))
            {
                NetImgui::Disconnect();
            }
        }
        else if (NetImgui::IsConnectionPending())
        {
            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 0.2f, 1.0f));
            ImGui::Text("○ Connecting...");
            ImGui::PopStyleColor();
        }
        else
         {
             ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.2f, 0.2f, 1.0f));
             ImGui::Text("✗ Disconnected");
             ImGui::PopStyleColor();
             
             if (ImGui::Button("Connect"))
             {
                 printf("Listening for server connection on port %d...\n", NetImgui::kDefaultClientPort);
                 NetImgui::ConnectFromApp("BaseExample");
             }
         }
        
        ImGui::EndMainMenuBar();
    }

    // Main window
    ImGui::SetNextWindowPos(ImVec2(50, 50), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(400, 300), ImGuiCond_FirstUseEver);
    
    if (ImGui::Begin("Base Example Window", nullptr))
    {
        // Status section
        ImGui::Text("Connection Status:");
        ImGui::Indent();
        {
            ImGui::Text("  Is Connected:     %s", g_IsConnected ? "Yes" : "No");
            ImGui::Text("  Drawing Remote:   %s", NetImgui::IsDrawingRemote() ? "Yes" : "No");
            ImGui::Text("  Server Port:      %d", NetImgui::kDefaultServerPort);
        }
        ImGui::Unindent();
        
        ImGui::NewLine();
        ImGui::Separator();
        ImGui::NewLine();
        
        // Controls section
        ImGui::Text("Controls:");
        ImGui::Indent();
        {
            // Slider
            ImGui::SliderFloat("Slider Value", &g_Settings.sliderValue, 0.0f, 1.0f);
            
            // Checkbox
            ImGui::Checkbox("Enable Feature", &g_Settings.checkboxValue);
            
            // Text input
            ImGui::InputText("Text Input", g_Settings.textBuffer, IM_ARRAYSIZE(g_Settings.textBuffer));
            
            // Button with counter
            if (ImGui::Button("Increment"))
            {
                g_Settings.counter++;
            }
            ImGui::SameLine();
            ImGui::Text("Counter: %d", g_Settings.counter);
        }
        ImGui::Unindent();
        
        ImGui::NewLine();
        ImGui::Separator();
        ImGui::NewLine();
        
        // Info section
        ImGui::TextColored(ImVec4(0.6f, 0.6f, 0.6f, 1.0f), 
            "This UI is being rendered remotely by the NetImgui Server.");
        
        if (NetImgui::IsDrawingRemote())
        {
            ImGui::TextColored(ImVec4(0.2f, 1.0f, 0.2f, 1.0f), 
                "✓ You are viewing this through NetImgui!");
        }
    }
    ImGui::End();

    // Show Dear ImGui demo window (optional, useful for testing)
    static bool showDemo = true;
    if (showDemo)
    {
        ImGui::ShowDemoWindow(&showDemo);
    }

    // End the frame and send to server
    NetImgui::EndFrame();
}

//-------------------------------------------------------------------------------------------------
// Main Entry Point
//-------------------------------------------------------------------------------------------------
int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    // Initialize application
    if (!App_Startup())
    {
        fprintf(stderr, "Failed to start application\n");
        return 1;
    }

    // Main loop
    printf("Starting main loop (Ctrl+C to quit)...\n\n");
    
    while (!g_Quit)
    {
        // Update connection state
        App_UpdateConnection();
        
        // Render UI (only when connected and server requests it)
        App_Draw();
        
        // Limit frame rate to reduce CPU usage
        // The NetImgui frame skipping also helps here
        std::this_thread::sleep_for(std::chrono::milliseconds(8));  // ~120 FPS max
    }

    // Shutdown
    App_Shutdown();
    
    return 0;
}
