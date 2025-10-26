#ifndef SINGLE_SPIN_MANUAL_CLUSTER_HPP
#define SINGLE_SPIN_MANUAL_CLUSTER_HPP

#include "interface_manual_cluster_creator.hpp"
#include "interface_multi_spin.hpp"
#include "wolff_algorithms/single_spin_wolff_algorithm.hpp"
#include "spin_handlers/abstract_spin_handler.hpp"
#include "spin_handlers/manual_spin_handler/manual_controller.hpp"

class SingleSpinManualClusterCreator: public IManualClusterCreator , public IMultiSpin
{
    SingleSpinWolffAlgorithm m_wolff{}; 
    ManualController m_controller{};
    AbstractSpinHandler* m_spinHandler{};
    size_t m_spinsPerFrame{1};
    size_t m_spinCounter{};
    void checkWaitingStatus();
    bool initClusterManually(AbstractWolffArray2d& spinMatrix) override;
public:

    SingleSpinManualClusterCreator(AbstractSpinHandler* state);
    ~SingleSpinManualClusterCreator() = default;
    void setSpinPerFrame(size_t N) override;
    void resetCount() override;
    void activateManualController() override;
    void createCluster(AbstractWolffArray2d& spinMatrix, std::mt19937& rng, float temperature) override;
};

#endif