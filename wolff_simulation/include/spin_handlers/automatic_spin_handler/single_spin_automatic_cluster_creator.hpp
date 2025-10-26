#ifndef SINGLE_SPIN_AUTOMATIC_CLUSTER_CREATOR_HPP
#define SINGLE_SPIN_AUTOMATIC_CLUSTER_CREATOR_HPP

#include "interface_cluster_creator.hpp"
#include "interface_multi_spin.hpp"
#include "wolff_algorithms/single_spin_wolff_algorithm.hpp"
#include "spin_handlers/automatic_spin_handler/automatic_controller.hpp"
#include "spin_handlers/abstract_spin_handler.hpp"

// class SingleSpinAutomaticClusterCreator: public IClusterCreator                     
//     {
//     AutomaticController m_controller{};
//     SingleSpinWolffAlgorithm m_wolff{};
//     AbstractSpinHandler* m_spinHandler{};

//     void initCluster(IGuiArray2d& spinMatrix, std::mt19937& rng);
// public:



//     SingleSpinAutomaticClusterCreator(AbstractSpinHandler* parent_state);
//     ~SingleSpinAutomaticClusterCreator() = default;
//     void createCluster(IGuiArray2d& spinMatrix, std::mt19937& rng, float temperature) override;
// };
class SingleSpinAutomaticClusterCreator: public IClusterCreator , public IMultiSpin   // 
{
    AutomaticController m_controller{};
    SingleSpinWolffAlgorithm m_wolff{};
    AbstractSpinHandler* m_spinHandler{};
    size_t m_spinsPerFrame{1};
    size_t m_spinCounter{};
    void initCluster(AbstractWolffArray2d& spinMatrix, std::mt19937& rng);
public:
    // setNumberOfUpdates(size_t N);
    void setSpinPerFrame(size_t N) override;
    void resetCount() override;
    SingleSpinAutomaticClusterCreator(AbstractSpinHandler* parent_state);
    ~SingleSpinAutomaticClusterCreator() = default;
    void createCluster(AbstractWolffArray2d& spinMatrix, std::mt19937& rng, float temperature) override;
};
#endif