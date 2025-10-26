#include "wolff_algorithms/full_wolff_algorithm.hpp"

void FullWolffAlgorithm::performWolffAlgorithm(AbstractWolffArray2d &spinMatrix, std::mt19937 &rng, float temperature)
{
    while(!isEmptyQueue())
    {
        createNewNeighbourhood(spinMatrix);
        for (auto& ngbrPosition : m_neighbourhood)//const auto!!
        {
            if( (spinMatrix.at(ngbrPosition) == getSeedSpin()) && acceptMove(temperature, rng) ) // seedSpin could be retrieved from matrix.
            {
                addToClusterQueue(ngbrPosition);
                spinMatrix.at(ngbrPosition) *= -1;
            }
        }
    }
}