#ifndef AUTOMATIC_CONTROLLER_HPP
#define AUTOMATIC_CONTROLLER_HPP

#include <random>
#include "interface_gui_array_2d.hpp"

struct AutomaticController 
{
    inline static ArrayPoint getSeedRandom(const IGuiArray2d& spinMatrix, std::mt19937& rng) // Put this in WolffDataStructure?
    {
        return {( static_cast<int64_t>(rng()) )%spinMatrix.getWidth(), ( static_cast<int64_t>(rng()) )%spinMatrix.getHeight()}; // Use Unamed Return value optimisation
    }
};

#endif