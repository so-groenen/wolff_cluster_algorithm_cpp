#ifndef SINGLE_SPIN_AUTOMATIC_CLUSTER_CREATOR_HPP
#define SINGLE_SPIN_AUTOMATIC_CLUSTER_CREATOR_HPP

#include "interface_cluster_creator.hpp"
#include "wolff_algorithms/single_spin_wolff_algorithm.hpp"
#include "spin_handlers/automatic_spin_handler/automatic_controller.hpp"
#include "spin_handlers/abstract_spin_handler.hpp"

class SingleSpinAutomaticClusterCreator: public IClusterCreator                     
    {
    AutomaticController m_controller{};
    SingleSpinWolffAlgorithm m_wolff{};
    AbstractSpinHandler* m_spinHandler{};

    void initCluster(IGuiArray2d& spinMatrix, std::mt19937& rng);
public:

    SingleSpinAutomaticClusterCreator(AbstractSpinHandler* parent_state);
    ~SingleSpinAutomaticClusterCreator() = default;
    void createCluster(IGuiArray2d& spinMatrix, std::mt19937& rng, float temperature) override;
};

#endif