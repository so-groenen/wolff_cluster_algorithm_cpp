#include "wolff_algorithms/base_wolff_algorithm.hpp"

static constexpr float INVERSE_TEMP_CUTOFF {10E6f};

const int& BaseWolffAlgorithm::getSeedSpin() const    //Can be private
{
    return m_seedSpin;
}
bool BaseWolffAlgorithm::acceptMove(float temperature, std::mt19937& rng) const  //Can be private
{
    std::uniform_real_distribution<float> distrib{0.0f, 1.0f};
    float J     {1.f};
    float beta  {(temperature > 0.f)? (1.0f/temperature) : INVERSE_TEMP_CUTOFF};
    float r     {distrib(rng)}; // {static_cast<float>(rng()) / static_cast<float>(rng.max())};
    bool accept  {r < (1.f - std::exp(-2.f*J*beta)) };
    return (accept);
}
void BaseWolffAlgorithm::createNewNeighbourhood(AbstractWolffArray2d& array) 
{
    const ArrayPoint spinPosition  {m_clusterQueue.front()};
    m_clusterQueue.pop();
    array.setNeighbourhood(spinPosition, m_neighbourhood);
}
void BaseWolffAlgorithm::setSeedSpin(AbstractWolffArray2d& spinMatrix) //Can be private, renamed to seedSpin
{
    m_seedPosition = spinMatrix.seed.getSeed();
    m_seedSpin     = spinMatrix.at(m_seedPosition);
}
void BaseWolffAlgorithm::addToClusterQueue(const ArrayPoint& point) //Can be private
{
    m_clusterQueue.emplace(point);
}
// void BaseWolffAlgorithm::setSeedPosition(const ArrayPoint& point) //Is not needed, seed is carried by WolffArray2d
// {
//     m_seedPosition = point; 
// }
void BaseWolffAlgorithm::initQueue(AbstractWolffArray2d& spinMatrix)//, ArrayPoint seedPosition) //setting the seed is not this classes concerns
{
    // setSeedPosition(seedPosition);  // initQueue should retrived seedPosition
    setSeedSpin(spinMatrix);
    addToClusterQueue(m_seedPosition);
    spinMatrix.at(m_seedPosition) *= -1;    
}
bool BaseWolffAlgorithm::isEmptyQueue() const
{
    return m_clusterQueue.empty();
}
