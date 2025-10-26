#include "phys_gui/phys_backend.hpp"


namespace PhysBackend
{

    SDL_Window* AppWindow::WindowHandle() const
    {
        return m_window;
    }
    unsigned int AppWindow::ID() const
    {
        return SDL_GetWindowID(m_window);
    }
    float AppWindow::MainScale() const
    {
        return main_scale;
    }
    SDL_Window* AppWindow::GetCurrentWindowHandle()
    {
        return SDL_GL_GetCurrentWindow();
    }
    AppWindow::AppWindow(const char* title, unsigned int window_flags, int window_width, int window_heigth)
    {
    // From 2.0.18: Enable native IME.

// #ifdef _WIN32
//         ::SetProcessDPIAware();
// #endif
//         if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0)
//         {
//             throw std::runtime_error(std::format("Error: {} \n", SDL_GetError()));
//         }
            // Decide GL+GLSL versions
#if defined(IMGUI_IMPL_OPENGL_ES2)
        // GL ES 2.0 + GLSL 100 (WebGL 1.0)
        const char* glsl_version = "#version 100";
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
#elif defined(IMGUI_IMPL_OPENGL_ES3)
        // GL ES 3.0 + GLSL 300 es (WebGL 2.0)
        const char* glsl_version = "#version 300 es";
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
#elif defined(__APPLE__)
        // GL 3.2 Core + GLSL 150
        const char* glsl_version = "#version 150";
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG); // Always required on Mac
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
#else
        // GL 3.0 + GLSL 130
        const char* glsl_version = "#version 130";
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
#endif
        m_GLVersion = std::string_view{glsl_version};


#ifdef SDL_HINT_IME_SHOW_UI
        SDL_SetHint(SDL_HINT_IME_SHOW_UI, "1");
#endif

        // Create window with graphics context
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
        SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
        main_scale = ImGui_ImplSDL2_GetContentScaleForDisplay(0);
 
        m_window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, (int)(window_width * main_scale), (int)(window_heigth * main_scale), (SDL_WindowFlags)window_flags);
        if (m_window == nullptr)
        {
            throw std::runtime_error(std::format("Error: SDL_CreateWindow(): {} \n", SDL_GetError()));
        }
    }
    void AppWindow::Swap()
    {
        SDL_GL_SwapWindow(m_window);
    }
    const char* AppWindow::GLVersion() const
    {
        return m_GLVersion.data();
    }
    bool AppWindow::IsMinimized()
    {
        return (SDL_GetWindowFlags(m_window) & SDL_WINDOW_MINIMIZED);
    }
    AppWindow::~AppWindow()
    {
        SDL_DestroyWindow(m_window);
    }
}
 