#include "phys_gui/phys_runner/game_loop.hpp"

ImVec4 g_clear_color{};
bool g_heap_runner_init{};
bool g_native_runner_init{};

void HandleEvents(const PhysBackend::AppWindow& window, SDL_Event& event, bool& is_done)
{
    while (SDL_PollEvent(&event))           // --> pass OS inputs/events to SDL
    {
        ImGui_ImplSDL2_ProcessEvent(&event); //--> pass SDL events to IMGUI
        if (event.type == SDL_QUIT)
            is_done = true;
        if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == window.ID())
            is_done = true;
    }
}
void BeginDraw(const PhysBackend::AppWindow& window)
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();
}
void EndDraw(PhysBackend::AppWindow& window, PhysBackend::OpenGLContext& open_gl_context, PhysBackend::ImGuiManager& imgui_manager, ImVec4 background_color)
{
    ImGui::Render();
    int display_w = ImGui::GetIO().DisplaySize.x;  // imgui can pick up display size change
    int display_h = ImGui::GetIO().DisplaySize.y;   
    glViewport(0, 0, display_w, display_h);         // and pass it to the openGL viewport
    glClearColor(background_color.x * background_color.w, background_color.y * background_color.w, background_color.z * background_color.w, background_color.w);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        imgui_manager.UpdatePlatformWindows();
        imgui_manager.RenderPlatformWindowsDefault();
        open_gl_context.MakeCurrent(window); 
    }
    else
    {
        open_gl_context.MakeCurrent(window); 
    }
    window.Swap();
}
