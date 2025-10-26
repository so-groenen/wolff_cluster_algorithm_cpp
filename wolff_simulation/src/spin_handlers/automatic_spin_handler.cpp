#include "spin_handlers/automatic_spin_handler.hpp"

ControlMode AutomaticSpinHandler::getControlMode() const
{
    return ControlMode::Automatic;
}


void AutomaticSpinHandler::setClusterCreator(SpinMode mode)
{
    setSpinMode(mode);
    // switch (getSpinMode())
    // {
    // case SpinMode::FullSpin:
    //     m_current = &m_autoFull;
    //     break;
    // case SpinMode::SingleSpin:
    //     m_autoSingle.resetCount();
    //     m_autoSingle.setSpinPerFrame(1);
    //     m_current = &m_autoSingle;
    //     break;

    // default:
    //     break;
    // }
    if (getSpinMode() == SpinMode::FullSpin)
    {
        m_current = &m_autoFull;
    }
    else
    {
        size_t N {spinModeToNum(getSpinMode())};
        // m_autoSingle.resetCount();
        m_autoSingle.setSpinPerFrame(N);
        m_current = &m_autoSingle;
    }
    
}
AutomaticSpinHandler::AutomaticSpinHandler()
{
}
void AutomaticSpinHandler::activateSpinHandler()
{
    m_autoSingle.resetCount();
    setState(State::ACTIF);
    // setToActif();
}
void AutomaticSpinHandler::createCluster(AbstractWolffArray2d& spinMatrix, std::mt19937& rng, float temperature)
{
    m_current->createCluster(spinMatrix, rng, temperature);
}

