#include "wolff_algorithms/single_spin_wolff_algorithm.hpp"


// bool SingleSpinWolffAlgorithm::isUpdatedCluster() const // should be private
// {
//     return (m_visitedNeighbours < m_neighbourhood.size());
// }
// bool SingleSpinWolffAlgorithm::attempt_Single_Spin_UpdateAbstractWolffArray2d& SpinMatrix, std::mt19937& rng, float temperature)
// {
//     ArrayPoint ngbrPosition;
//     while(m_visitedNeighbours < m_neighbourhood.size())
//     {
//         ngbrPosition = m_neighbourhood.at(m_visitedNeighbours);
//         if( (SpinMatrix.at(ngbrPosition) == getSeedSpin()) && acceptMove(temperature, rng) ) // seedSpin could be retrieved from matrix.
//         { 
//             addToClusterQueue(ngbrPosition);
//             SpinMatrix.at(ngbrPosition) *= -1;
//             return isUpdatedCluster();  // true
//         }
//         m_visitedNeighbours++;
//     }
//     return isUpdatedCluster(); //false
// }

bool SingleSpinWolffAlgorithm::attemptSingleSpinUpdate(AbstractWolffArray2d& spinMatrix, std::mt19937& rng, float temperature)
{
    if(isNewNeighbourhood() || isNeighbourhoodVisited())
    {
        createNewNeighbourhood(spinMatrix);
        m_visitedNeighbours = 0;                                      
    }       

    while(m_visitedNeighbours < m_neighbourhood.size())
    {
        ArrayPoint ngbrPosition {m_neighbourhood.at(m_visitedNeighbours)};

        if( (spinMatrix.at(ngbrPosition) == getSeedSpin()) && acceptMove(temperature, rng) ) 
        { 
            addToClusterQueue(ngbrPosition);
            spinMatrix.at(ngbrPosition) *= -1;
            m_visitedNeighbours++;
            return true;
        }
        m_visitedNeighbours++;

    }
    return false;  
}
bool SingleSpinWolffAlgorithm::isNewNeighbourhood() const
{
    return ( m_visitedNeighbours == 0);
}
bool SingleSpinWolffAlgorithm::isNeighbourhoodVisited() const
{
    return (m_visitedNeighbours == m_neighbourhood.size());
}
// void SingleSpinWolffAlgorithm::resetSpinCounter()
// {
//     m_visitedNeighbours = 0;
// }
// void SingleSpinWolffAlgorithm::updateSpinCounter()
// {
//     m_visitedNeighbours++;
// }
