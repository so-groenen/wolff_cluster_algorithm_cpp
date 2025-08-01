#pragma once
#include "base_wolff_algorithm.hpp"

class FullWolffAlgorithm : public BaseWolffAlgorithm  
{
public:
    void performWolffAlgorithm(IGuiArray2d& spinMatrix, std::mt19937& rng, float temperature);
};