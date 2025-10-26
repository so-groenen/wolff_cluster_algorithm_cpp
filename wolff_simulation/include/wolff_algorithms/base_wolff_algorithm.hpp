#ifndef BASE_WOLFF_HPP
#define BASE_WOLFF_HPP
#include "interface_gui_array_2d.hpp"
#include <random>
#include <queue>


using periodic_array_2d::ArrayPoint;
using queue_t         = std::queue<ArrayPoint>;
using neighbourhood_t = std::array<ArrayPoint,4>;


class BaseWolffAlgorithm
{
    int     m_seedSpin{};
    ArrayPoint  m_seedPosition{};
    queue_t     m_clusterQueue{};
public:
    neighbourhood_t m_neighbourhood{}; 
    const int& getSeedSpin() const ;
    bool acceptMove(float temperature, std::mt19937& rng) const;
    void createNewNeighbourhood(AbstractWolffArray2d& array) ;
    void setSeedSpin(AbstractWolffArray2d& spinMatrix);
    void addToClusterQueue(const ArrayPoint& point) ;
    // void setSeedPosition(const ArrayPoint& point);
    void initQueue(AbstractWolffArray2d& spinMatrix);// ArrayPoint seedPosition);
    bool isEmptyQueue() const;
};

#endif