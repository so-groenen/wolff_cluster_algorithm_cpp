#pragma once

#include "base_wolff_algorithm.hpp"
class SingleSpinWolffAlgorithm : public BaseWolffAlgorithm  // use composition here? FullWolffAlgorithm has a data structure
{
    size_t m_spinCounter = 0;
    bool isUpdatedCluster() const;
public:
    bool attemptSingleSpinUpdate(IGuiArray2d& SpinMatrix, std::mt19937& rng, float temperature);
    bool isNewNeighbourhood() const;
    bool isNeighbourhoodVisited() const;
    void resetSpinCounter();
    void updateSpinCounter();
};