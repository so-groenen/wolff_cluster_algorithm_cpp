#include "phys_gui/phys_runner.hpp"
 

namespace PhysRunner
{
    bool NativeRunner::s_native_done{};
    SDL_Event NativeRunner::s_native_event{};
    SDL_Event  NativeRunner::Event()
    {
        return s_native_event;
    }
    void  NativeRunner::Close()
    {
        s_native_done = true;
    }
}