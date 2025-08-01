#include "wolff_algorithms/full_wolff_algorithm.hpp"

void FullWolffAlgorithm::performWolffAlgorithm(IGuiArray2d &spinMatrix, std::mt19937 &rng, float temperature)
{
    while(!isEmptyQueue())
    {
        createNewNeighbourhood(spinMatrix);
        for (auto& ngbrPosition : m_neighbourhood)
        {
            if( (spinMatrix.at(ngbrPosition) == getSeedSpin()) && acceptMove(temperature, rng) )
            {
                addToClusterQueue(ngbrPosition);
                spinMatrix.at(ngbrPosition) *= -1;
            }
        }
    }
}