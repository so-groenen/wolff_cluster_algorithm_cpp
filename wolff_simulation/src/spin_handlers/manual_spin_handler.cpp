#include "spin_handlers/manual_spin_handler.hpp"

ControlMode ManualSpinHandler::getControlMode() const
{
    return ControlMode::Manual;
}
void ManualSpinHandler::setClusterCreator(SpinMode mode) 
{
    setSpinMode(mode);
    // switch ( getSpinMode())
    // {
    // case SpinMode::SingleSpin:
    //     m_manualSingle.resetCount();
    //     m_manualSingle.setSpinPerFrame(1);
    //     m_current = &m_manualSingle;
    //     break;
    // case SpinMode::FullSpin:
    //     m_current = &m_manualFull;
    //     break;
    // default:
    //     break;
    // }
    if (getSpinMode() == SpinMode::FullSpin)
    {
        m_current = &m_manualFull;
    }
    else
    {
        size_t N {spinModeToNum(getSpinMode())};
        // m_manualSingle.resetCount();
        m_manualSingle.setSpinPerFrame(N);
        m_current = &m_manualSingle;
    }

}
void ManualSpinHandler::activateSpinHandler() 
{
    m_current->activateManualController(); // we need to wait user input => activating means waiting.
    m_manualSingle.resetCount();
    setState(State::ACTIF);
    // setToActif();
}
void ManualSpinHandler::createCluster(AbstractWolffArray2d& spinMatrix, std::mt19937& rng, float temperature) 
{
    m_current->createCluster(spinMatrix, rng, temperature);
}
