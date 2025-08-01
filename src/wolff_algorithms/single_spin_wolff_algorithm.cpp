#include "wolff_algorithms/single_spin_wolff_algorithm.hpp"


bool SingleSpinWolffAlgorithm::isUpdatedCluster() const // should be private
{
    return (m_spinCounter < m_neighbourhood.size());
}
bool SingleSpinWolffAlgorithm::attemptSingleSpinUpdate(IGuiArray2d& SpinMatrix, std::mt19937& rng, float temperature)
{
    ArrayPoint ngbrPosition;
    while(m_spinCounter < m_neighbourhood.size())
    {
        ngbrPosition = m_neighbourhood.at(m_spinCounter);
        if( (SpinMatrix.at(ngbrPosition) == getSeedSpin()) && acceptMove(temperature, rng) )
        {
            addToClusterQueue(ngbrPosition);
            SpinMatrix.at(ngbrPosition) *= -1;
            return isUpdatedCluster();  
        }
        m_spinCounter++;
    }
    return isUpdatedCluster();
}
bool SingleSpinWolffAlgorithm::isNewNeighbourhood() const
{
    return ( m_spinCounter == 0);
}
bool SingleSpinWolffAlgorithm::isNeighbourhoodVisited() const
{
    return (m_spinCounter == m_neighbourhood.size());
}
void SingleSpinWolffAlgorithm::resetSpinCounter()
{
    m_spinCounter = 0;
}
void SingleSpinWolffAlgorithm::updateSpinCounter()
{
    m_spinCounter++;
}
