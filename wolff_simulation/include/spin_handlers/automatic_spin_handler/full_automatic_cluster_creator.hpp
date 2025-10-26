#ifndef FULL_AUTOMATIC_CLUSTER_CREATOR_HPP
#define FULL_AUTOMATIC_CLUSTER_CREATOR_HPP

#include "interface_cluster_creator.hpp"
#include "wolff_algorithms/full_wolff_algorithm.hpp"
#include "spin_handlers/automatic_spin_handler/automatic_controller.hpp"
#include "spin_handlers/abstract_spin_handler.hpp"

// class FullAutomaticClusterCreator: public IClusterCreator 
// {
//     AutomaticController m_controller{};
//     FullWolffAlgorithm m_wolff{};
//     AbstractSpinHandler* m_spinHandler;               

//     void setRandomPosition(const ArrayPoint& seedPosition);
//     void initCluster(AbstractWolffArray2d& spinMatrix, std::mt19937& rng) ;
// public:
//     FullAutomaticClusterCreator(AbstractSpinHandler* parent_state);
//     ~FullAutomaticClusterCreator() = default;
//     void createCluster(AbstractWolffArray2d& spinMatrix, std::mt19937& rng, float temperature) override;
// };

class FullAutomaticClusterCreator: public IClusterCreator 
{
    AutomaticController m_controller{};
    FullWolffAlgorithm m_wolff{};
    AbstractSpinHandler* m_spinHandler;               

    // void setRandomPosition(const ArrayPoint& seedPosition);
    void initCluster(AbstractWolffArray2d& spinMatrix, std::mt19937& rng) ;
public:
    FullAutomaticClusterCreator(AbstractSpinHandler* parent_state);
    ~FullAutomaticClusterCreator() = default;
    void createCluster(AbstractWolffArray2d& spinMatrix, std::mt19937& rng, float temperature) override;
};

#endif