#include "phys_gui/phys_runner.hpp"
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

namespace PhysRunner 
{
    std::unique_ptr<PhysBackend::AppWindow>     CrossPlatformRunner::s_window{};
    std::unique_ptr<PhysBackend::OpenGLContext> CrossPlatformRunner::s_gl_context{};
    std::unique_ptr<PhysBackend::ImGuiManager>  CrossPlatformRunner::s_imgui_manager{};
    std::unique_ptr<IPhysGuiApp> CrossPlatformRunner::s_app{};
    ImVec4 CrossPlatformRunner::s_background_color{};
    SDL_Event CrossPlatformRunner::s_event{};
    bool CrossPlatformRunner::s_is_done{};
    
    SDL_Event CrossPlatformRunner::Event()
    {
        return s_event;
    }
    void CrossPlatformRunner::Close()
    {
        s_is_done = true;
    }
    void CrossPlatformRunner::ReleaseResources()
    {
        s_window.reset();
        s_gl_context.reset();
        s_imgui_manager.reset();
    }
    CrossPlatformRunner CrossPlatformRunner::Setup(Options options)
    {
        if(g_native_runner_init)
        {
            throw std::runtime_error("PhysRunner::CrossPlatformRunner: Cannot initiliaze, a native application is still running.\n");
        }            

        if(!g_heap_runner_init)
        {
            PhysBackend::SDLBackend::Init();
            //  classes to manage the resources of the low level C Api of SDL & OpenGL
            // which are wrapped in smart pointers
            s_window        = std::make_unique<PhysBackend::AppWindow>(options.title, options.SDL_windows_flags, options.width, options.height);
            s_gl_context    = std::make_unique<PhysBackend::OpenGLContext>(*s_window.get());
            s_imgui_manager = std::make_unique<PhysBackend::ImGuiManager>();
            s_background_color = options.background_color;
            s_imgui_manager->SetConfigFlags(options.imgui_config_flags);
            if (options.is_vsync_active)
            {
                s_gl_context->SetSwapInterval(1);
            }
            else
            {
                s_gl_context->SetSwapInterval(0);
            }

            ImGui::StyleColorsDark();

            s_imgui_manager->SetupBackends(*s_window.get(), *s_gl_context.get());
            g_heap_runner_init = true;
        }
        return CrossPlatformRunner{};
    }
    void CrossPlatformRunner::UpdateWebApplication()  // This is our "static" function that can be used with emscripten!
    {
        HandleEvents(*s_window, s_event, s_is_done);
        
        BeginDraw(*s_window);
            s_app->Update();
        EndDraw(*s_window, *s_gl_context, *s_imgui_manager, s_background_color);
    }
    void CrossPlatformRunner::Run(std::unique_ptr<IPhysGuiApp> app)
    {
        s_is_done = false;
        s_app  = std::move(app);

    #ifdef __EMSCRIPTEN__
        emscripten_set_main_loop(CrossPlatformRunner::UpdateWebApplication, 0, true);
    #else
        while (!s_is_done)
        {
            HandleEvents(*s_window, s_event, s_is_done);
            if (s_window->IsMinimized())
            {
                SDL_Delay(10);
                continue;
            }
            BeginDraw(*s_window);
                s_app->Update();
            EndDraw(*s_window, *s_gl_context, *s_imgui_manager, s_background_color);
        }
        // CrossPlatformRunner::ReleaseResources();
        // PhysBackend::SDLBackend::Quit();
        // g_heap_runner_init = false;
    #endif
    }


    CrossPlatformRunner::~CrossPlatformRunner()
    {
        CrossPlatformRunner::ReleaseResources(); // "Force release resource" so that SDL_Quit get called after window & context is destroyed,
        PhysBackend::SDLBackend::Quit();         // Otherwise we can use a Smart Pointer for SDL_Quit/SDL_init but this is overkill...
        g_heap_runner_init = false;
    }
}