#ifndef PHYS_BACKEND2_HPP
#define PHYS_BACKEND2_HPP

#include "phys_graphics.hpp"
#include <iostream>
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"
#include <stdio.h>

#include <SDL.h>
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <SDL_opengles2.h>
#else
#include <SDL_opengl.h>
#endif
#ifdef _WIN32
#include <windows.h>       
#endif

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif


namespace PhysBackend
{
    namespace SDLBackend
    {
        void Init();
        void Quit();
    };
     
// 3 different classes to manage ressources of the low-level C/C++-API (OpenGL context + SDL window + imgui context)
class AppWindow
{
    std::string_view m_GLVersion{};
    float main_scale{};
    SDL_Window* m_window{};
public:
    SDL_Window* WindowHandle() const;
    unsigned int ID() const;
    float MainScale() const;
    static SDL_Window* GetCurrentWindowHandle();
    AppWindow(const char* title, unsigned int window_flags, int window_width, int window_heigth);
    void Swap();
    const char* GLVersion() const;
    bool IsMinimized();
    ~AppWindow();
};



class OpenGLContext
{
    SDL_GLContext m_gl_context{};
public:
    OpenGLContext(const AppWindow& app_window);
    OpenGLContext(SDL_GLContext raw_gl_context);
    void MakeCurrent(const AppWindow& app_window);
    void* Get() const;
    static OpenGLContext GetCurrentContext();
    void SetSwapInterval(int interval);
    ~OpenGLContext();
};


class ImGuiManager
{
    // static ImGuiManager s_manager;
public:
    ImGuiManager();
    void SetupBackends(const AppWindow& app_window, const OpenGLContext& gl_context);
    ImGuiManager& SetConfigFlags(ImGuiConfigFlags flags);
    void UpdatePlatformWindows();
    void RenderPlatformWindowsDefault();
    ~ImGuiManager();
};
}

#endif
 
