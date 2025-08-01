#ifndef AUTOMATIC_SPIN_HANDLER_HPP
#define AUTOMATIC_SPIN_HANDLER_HPP

#include "spin_handlers/abstract_spin_handler.hpp"
#include "spin_handlers/automatic_spin_handler/full_automatic_cluster_creator.hpp"
#include "spin_handlers/automatic_spin_handler/single_spin_automatic_cluster_creator.hpp"

class AutomaticSpinHandler: public AbstractSpinHandler  
{
    SpinMode m_spinMode{};
    IClusterCreator* m_current{};
    FullAutomaticClusterCreator       m_autoFull{this};     
    SingleSpinAutomaticClusterCreator m_autoSingle{this};
    void setSpinMode(SpinMode mode) override;
public:
    AutomaticSpinHandler();
    ~AutomaticSpinHandler() = default;
    void activateSpinHandler() override;
    void createCluster(IGuiArray2d& spinMatrix, std::mt19937& rng, float temperature) override;
};

#endif