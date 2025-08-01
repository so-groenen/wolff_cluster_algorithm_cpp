#ifndef FULL_MANUAL_CLUSTER_CREATOR_HPP
#define FULL_MANUAL_CLUSTER_CREATOR_HPP

#include "interface_manual_cluster_creator.hpp"
#include "wolff_algorithms/full_wolff_algorithm.hpp"
#include "spin_handlers/abstract_spin_handler.hpp"
#include "spin_handlers/manual_spin_handler/manual_controller.hpp"

class FullManualClusterCreator: public IManualClusterCreator // inherit from IClusterCreator & WolffState, put ManualState as composition
{
    FullWolffAlgorithm m_wolff{};
    ManualController m_controller{};
    AbstractSpinHandler* m_handler_state{};
    bool initClusterManually(IGuiArray2d& spinMatrix) override;
public:
    FullManualClusterCreator(AbstractSpinHandler* state);
    ~FullManualClusterCreator() = default;
    void activateManualClusterCreator() override;
    void createCluster(IGuiArray2d& spinMatrix, std::mt19937& rng, float temperature) override;
};

#endif