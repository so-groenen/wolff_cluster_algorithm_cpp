#ifndef AUTOMATIC_CONTROLLER_HPP
#define AUTOMATIC_CONTROLLER_HPP

#include <random>
#include "interface_gui_array_2d.hpp"

// struct AutomaticController 
// {
//     inline static ArrayPoint getSeedRandom(const IGuiArray2d& spinMatrix, std::mt19937& rng) // Put this in WolffDataStructure?
//     {
//         return {( static_cast<int>(rng()) )%spinMatrix.getWidth(), ( static_cast<int>(rng()) )%spinMatrix.getHeight()}; // Use Unamed Return value optimisation
//     }
// };

struct AutomaticController 
{
    inline static ArrayPoint getSeedRandom(const AbstractWolffArray2d& spinMatrix, std::mt19937& rng) // Put this in WolffDataStructure?
    {
        // std::uniform_int_distribution<int> rand_x(0,spinMatrix.getWidth()-1);
        // std::uniform_int_distribution<int> rand_y(0,spinMatrix.getHeight()-1);
        // return {rand_x(rng), rand_y(rng)};
        return {( static_cast<int>(rng()) )%spinMatrix.getWidth(), ( static_cast<int>(rng()) )%spinMatrix.getHeight()}; // Use Unamed Return value optimisation
    }
};


#endif