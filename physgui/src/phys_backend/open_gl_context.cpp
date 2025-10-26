
#include "phys_gui/phys_backend.hpp"


namespace PhysBackend
{
    OpenGLContext::OpenGLContext(const AppWindow& app_window)
    {
        m_gl_context = SDL_GL_CreateContext(app_window.WindowHandle());
        if (m_gl_context == nullptr)
        {
            throw std::runtime_error(std::format("Error: SDL_GL_CreateContext() {} \n", SDL_GetError()));
        }

#ifndef IMGUI_IMPL_OPENGL_ES2   
        PhysGraphics::LoadOpenGl(reinterpret_cast<GLADloadproc>(SDL_GL_GetProcAddress));  // Load openGL functions for our mini API!
#endif
        SDL_GL_MakeCurrent(app_window.WindowHandle(), m_gl_context);
    }
    OpenGLContext::OpenGLContext(SDL_GLContext raw_gl_context)
        : m_gl_context{raw_gl_context}
    {
    }
    void OpenGLContext::MakeCurrent(const AppWindow& app_window)
    {
        SDL_GL_MakeCurrent(app_window.WindowHandle(), m_gl_context);
    }
    void* OpenGLContext::Get() const
    {
        return m_gl_context;
    }
    OpenGLContext OpenGLContext::GetCurrentContext()
    {
        SDL_GLContext backup_current_context = SDL_GL_GetCurrentContext();
        return {backup_current_context};
    }
    void OpenGLContext::SetSwapInterval(int interval)
    {
        SDL_GL_SetSwapInterval(interval);
    }
    OpenGLContext::~OpenGLContext()
    {
        SDL_GL_DeleteContext(m_gl_context); 
    }
}