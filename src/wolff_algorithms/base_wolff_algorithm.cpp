#include "wolff_algorithms/base_wolff_algorithm.hpp"

static constexpr float INVERSE_TEMP_CUTOFF {10E6f};

const int64_t& BaseWolffAlgorithm::getSeedSpin() const    //Can be private
{
    return m_seedSpin;
}
bool BaseWolffAlgorithm::acceptMove(float temperature, std::mt19937& rng) const  //Can be private
{
    float J     {1.f};
    float beta  {(temperature > 0.f)? (1.0f/temperature) : INVERSE_TEMP_CUTOFF};
    float r      {static_cast<float>(rng()) / static_cast<float>(rng.max())};
    bool accept  {r < (1.f - std::exp(-2.f*J*beta)) };
    return (accept);
}
void BaseWolffAlgorithm::createNewNeighbourhood(IGuiArray2d& array) 
{
    const ArrayPoint spinPosition  {m_clusterQueue.front()};
    m_clusterQueue.pop();
    array.setNeighbourhood(spinPosition, m_neighbourhood);
}
void BaseWolffAlgorithm::setSeed(IGuiArray2d& spinMatrix) //Can be private
{
    m_seedSpin = spinMatrix.at(m_seedPosition);
}
void BaseWolffAlgorithm::addToClusterQueue(const ArrayPoint& point) //Can be private
{
    m_clusterQueue.emplace(point);
}
void BaseWolffAlgorithm::setSeedPosition(const ArrayPoint& point) //Can be private
{
    m_seedPosition = point;
}
void BaseWolffAlgorithm::initQueue(IGuiArray2d& spinMatrix, ArrayPoint seedPosition)
{
    setSeedPosition(seedPosition);
    setSeed(spinMatrix);
    addToClusterQueue(m_seedPosition);
    spinMatrix.at(m_seedPosition) *= -1;    
}
bool BaseWolffAlgorithm::isEmptyQueue() const
{
    return m_clusterQueue.empty();
}
