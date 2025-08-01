#ifndef MANUAL_SPIN_HANDLER_HPP
#define MANUAL_SPIN_HANDLER_HPP

#include "spin_handlers/abstract_spin_handler.hpp"
#include "spin_handlers/manual_spin_handler/full_manual_cluster_creator.hpp"
#include "spin_handlers/manual_spin_handler/single_spin_manual_cluster_creator.hpp"


class ManualSpinHandler : public AbstractSpinHandler  
{
    SpinMode m_spinMode;                
    IManualClusterCreator* m_current{};
    FullManualClusterCreator m_manualFull{this};
    SingleSpinManualClusterCreator m_manualSingle{this};

public:
    void setSpinMode(SpinMode mode) override;
    void activateSpinHandler() override;
    void createCluster(IGuiArray2d& spinMatrix, std::mt19937& rng, float temperature) override;
};

#endif