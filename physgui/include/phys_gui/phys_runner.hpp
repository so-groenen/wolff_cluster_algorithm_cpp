#ifndef PHYS_RUNNER_HPP
#define PHYS_RUNNER_HPP
#include <concepts>
#include "phys_backend.hpp"
#include <memory>
#include <expected>
#include "phys_runner/game_loop.hpp"

namespace PhysRunner
{
    class IPhysGuiApp
    {
    public:
        virtual void Update()  = 0;
        virtual ~IPhysGuiApp() = default;
    };
    
    template <typename F>
    concept UniqueAppLambda = std::invocable<F> && requires (F func)
    {
        {func()} -> std::convertible_to<std::unique_ptr<IPhysGuiApp>>;  
    };

    inline ImFont* LoadFontTTF(std::string_view path_to_ttf, float size_pixels = 0.0f, const ImFontConfig* font_cfg = nullptr, const ImWchar* glyph_ranges = nullptr)
    {
        return ImGui::GetIO().Fonts->AddFontFromFileTTF(path_to_ttf.data(), size_pixels, font_cfg, glyph_ranges);
    }

    struct Options
    {
        const char* title{"My Physics Application"};
        int width{1280};
        int height{720};
        ImGuiConfigFlags imgui_config_flags{ImGuiConfigFlags_NavEnableKeyboard | ImGuiConfigFlags_NavEnableGamepad};
        ImVec4 background_color{};
        bool is_vsync_active{};
        unsigned int SDL_windows_flags{SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI};
    };
    class CrossPlatformRunner  
    {
        CrossPlatformRunner()
        {
        }
        static std::unique_ptr<PhysBackend::AppWindow>     s_window;
        static std::unique_ptr<PhysBackend::OpenGLContext> s_gl_context;
        static std::unique_ptr<PhysBackend::ImGuiManager>  s_imgui_manager;
        static SDL_Event s_event;
        static bool s_is_done;
        
        static std::unique_ptr<IPhysGuiApp> s_app;
        static ImVec4 s_background_color;
        static void ReleaseResources();
        static CrossPlatformRunner Setup(Options options);
        void Run(std::unique_ptr<IPhysGuiApp> app);
    public:                     

        static void UpdateWebApplication(); 
        static SDL_Event Event();
        static void Close();    
        static void RunCrossPlatform(Options options, UniqueAppLambda auto lambda_app) 
        {
            // init the graphics context first!
            auto runner = CrossPlatformRunner::Setup(options);
            
            // call the lambda to allocate the app second!
            runner.Run(std::move(lambda_app()));
        }
        ~CrossPlatformRunner();
    };


    class NativeRunner  // Use class because we need s_native_done/s_native_event for the template function & keep them private
    {
        static bool s_native_done;
        static SDL_Event s_native_event;
    public:
        static SDL_Event Event();
        static void Close();
        template <typename App> 
        static void RunNative(Options options) requires std::derived_from<App, IPhysGuiApp>
        {
            g_native_runner_init = true;
            if (g_heap_runner_init)
            {
                throw std::runtime_error("RunNative: Only one application can be executed!\n");
            }
            PhysBackend::SDLBackend::Init();
            PhysBackend::AppWindow native_window(options.title, options.SDL_windows_flags, options.width, options.height);
            PhysBackend::OpenGLContext native_gl_context(native_window);
            PhysBackend::ImGuiManager imgui_manager{};
            imgui_manager.SetConfigFlags(options.imgui_config_flags);

            if (options.is_vsync_active)
            {
                native_gl_context.SetSwapInterval(1);
            }
            else
            {
                native_gl_context.SetSwapInterval(0);
            }

            ImGui::StyleColorsDark();
            
            imgui_manager.SetupBackends(native_window, native_gl_context);
            App native_app{};
            s_native_done = false;
            while (!s_native_done)
            {
                HandleEvents(native_window, s_native_event, s_native_done);
                if (native_window.IsMinimized())
                {
                    SDL_Delay(10);
                    continue;
                }
                BeginDraw(native_window);
                    native_app.Update();
                EndDraw(native_window, native_gl_context, imgui_manager, options.background_color);
            }
            PhysBackend::SDLBackend::Quit();
            g_native_runner_init = false;
        }
    };


}


#endif