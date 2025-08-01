#include "spin_handlers/manual_spin_handler.hpp"

void ManualSpinHandler::setSpinMode(SpinMode mode) 
{
    m_spinMode = mode;
    switch (m_spinMode)
    {
    case SpinMode::SingleSpin:
        m_current = &m_manualSingle;
        break;
    case SpinMode::FullSpin:
        m_current = &m_manualFull;
        break;
    default:
        break;
    }
}
void ManualSpinHandler::activateSpinHandler() 
{
    m_current->activateManualClusterCreator();
}
void ManualSpinHandler::createCluster(IGuiArray2d& spinMatrix, std::mt19937& rng, float temperature) 
{
    m_current->createCluster(spinMatrix, rng, temperature);
}
