#include "spin_handlers/automatic_spin_handler.hpp"



void AutomaticSpinHandler::setSpinMode(SpinMode mode)
{
    m_spinMode = mode;
    switch (m_spinMode)
    {
    case SpinMode::SingleSpin:
        m_current = &m_autoSingle;
        break;
    case SpinMode::FullSpin:
        m_current = &m_autoFull;
        break;
    default:
        break;
    }
}
AutomaticSpinHandler::AutomaticSpinHandler()
{
    setToActif();
    setSpinMode(SpinMode::SingleSpin);
}
void AutomaticSpinHandler::activateSpinHandler()
{
    setToActif();
}
void AutomaticSpinHandler::createCluster(IGuiArray2d& spinMatrix, std::mt19937& rng, float temperature)
{
    m_current->createCluster(spinMatrix, rng, temperature);
}

