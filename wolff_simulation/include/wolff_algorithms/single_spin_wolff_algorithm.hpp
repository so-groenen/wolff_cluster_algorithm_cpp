#pragma once

#include "base_wolff_algorithm.hpp"
class SingleSpinWolffAlgorithm : public BaseWolffAlgorithm  
{
    size_t m_visitedNeighbours = 0;       
    bool isNewNeighbourhood() const;
    bool isNeighbourhoodVisited() const;
    // void resetSpinCounter();
    // void updateSpinCounter();
public:
    // bool attempt_Single_Spin_UpdateAbstractWolffArray2d& SpinMatrix, std::mt19937& rng, float temperature);
    bool attemptSingleSpinUpdate(AbstractWolffArray2d& SpinMatrix, std::mt19937& rng, float temperature);


};