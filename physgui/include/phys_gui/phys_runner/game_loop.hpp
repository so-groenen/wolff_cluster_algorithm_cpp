#ifndef GAME_LOOP_HPP
#define GAME_LOOP_HPP

#include "phys_gui/phys_backend.hpp"


extern ImVec4 g_clear_color;
extern bool g_heap_runner_init;
extern bool g_native_runner_init;

void HandleEvents(const PhysBackend::AppWindow& window, SDL_Event& event, bool& is_done);
void BeginDraw(const PhysBackend::AppWindow& window);
void EndDraw(PhysBackend::AppWindow& window, PhysBackend::OpenGLContext& open_gl_context, PhysBackend::ImGuiManager& imgui_manager, ImVec4 background_color);
#endif