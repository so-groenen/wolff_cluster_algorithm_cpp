#include "phys_gui/phys_backend.hpp"


namespace PhysBackend
{
    namespace SDLBackend
    {
        void Init()
        {
    #ifdef _WIN32
            ::SetProcessDPIAware();
    #endif
            if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0)
            {
                throw std::runtime_error(std::format("Error: {} \n", SDL_GetError()));
            }
        }
        void Quit()
        {
            SDL_Quit();
        }
    };   
}