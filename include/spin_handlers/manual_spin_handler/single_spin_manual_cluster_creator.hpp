#ifndef SINGLE_SPIN_MANUAL_CLUSTER_HPP
#define SINGLE_SPIN_MANUAL_CLUSTER_HPP

#include "interface_manual_cluster_creator.hpp"
#include "wolff_algorithms/single_spin_wolff_algorithm.hpp"
#include "spin_handlers/abstract_spin_handler.hpp"
#include "spin_handlers/manual_spin_handler/manual_controller.hpp"

class SingleSpinManualClusterCreator: public IManualClusterCreator
{
    SingleSpinWolffAlgorithm m_wolff{}; 
    ManualController m_controller{};
    AbstractSpinHandler* m_spinHandler{};
    void checkWaitingStatus();
    bool initClusterManually(IGuiArray2d& spinMatrix) override;

public:
    SingleSpinManualClusterCreator(AbstractSpinHandler* state);
    ~SingleSpinManualClusterCreator() = default;
    void activateManualClusterCreator() override;
    void createCluster(IGuiArray2d& spinMatrix, std::mt19937& rng, float temperature) override;
};

#endif