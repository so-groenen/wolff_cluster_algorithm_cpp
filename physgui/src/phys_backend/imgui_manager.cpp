#include "phys_gui/phys_backend.hpp"


namespace PhysBackend
{
    ImGuiManager::ImGuiManager()
    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
    }
    void ImGuiManager::SetupBackends(const AppWindow& app_window, const OpenGLContext& gl_context)
    {
        ImGui_ImplSDL2_InitForOpenGL(app_window.WindowHandle(),  gl_context.Get());
        ImGui_ImplOpenGL3_Init(app_window.GLVersion());

        ImGuiStyle& style = ImGui::GetStyle();
        style.ScaleAllSizes(app_window.MainScale());        // Bake a fixed style scale. (until we have a solution for dynamic style scaling, changing this requires resetting Style + calling this again)
        style.FontScaleDpi = app_window.MainScale();  
    }
    ImGuiManager& ImGuiManager::SetConfigFlags(ImGuiConfigFlags flags)
    {
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= flags;   
        return *this;
    }
    void ImGuiManager::UpdatePlatformWindows()
    {
        ImGui::UpdatePlatformWindows();
    }
    void ImGuiManager::RenderPlatformWindowsDefault()
    {
        ImGui::RenderPlatformWindowsDefault();
    }
    ImGuiManager::~ImGuiManager()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplSDL2_Shutdown();
        ImGui::DestroyContext();
    }
}