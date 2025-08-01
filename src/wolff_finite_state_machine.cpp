#include "wolff_finite_state_machine.hpp"

void WolffFiniteStateMachine::updateModes()
{
    if (m_controlMode != m_nextControlMode)
    {
        m_controlMode = m_nextControlMode;
    }
    if (m_spinMode != m_nextSpinMode)
    {
        m_spinMode = m_nextSpinMode;
    }
}
void WolffFiniteStateMachine::setHandler(ControlMode mode)
{
    switch (mode)
    {
    case ControlMode::Automatic:
        m_currentHandler = &m_automaticHandler;
        break;
    case ControlMode::Manual:
        m_currentHandler = &m_manualHandler;
        break;
    default:
        break;
    }
}
bool WolffFiniteStateMachine::isNewSpinMode() const 
{
    return m_nextSpinMode != m_spinMode;
}
bool WolffFiniteStateMachine::isNewControlMode() const 
{
    return m_nextControlMode != m_controlMode;
}
WolffFiniteStateMachine::WolffFiniteStateMachine(ControlMode controlMode, SpinMode spinMode)
    : m_controlMode{controlMode}, 
        m_spinMode{spinMode},
        m_nextControlMode{controlMode},
        m_nextSpinMode{spinMode}
{
    setHandler(m_controlMode);
    m_currentHandler->setSpinMode(m_spinMode);
    m_currentHandler->activateSpinHandler();
}
void WolffFiniteStateMachine::handleEvents(ControlMode controlMode, SpinMode spinMode)
{
    if (!m_currentHandler->isActif() || (spinMode == m_spinMode && controlMode == m_controlMode) )
        return;
    
    if (spinMode != m_spinMode)
    {
        m_nextSpinMode = spinMode;
    }
    if (controlMode != m_controlMode)
    {
        m_nextControlMode = controlMode;
    }
    m_currentHandler->setToLeaving();
}
void WolffFiniteStateMachine::transitionState()
{
    if (!m_currentHandler->isFinished())
        return;
    
    m_currentHandler->deactivateSpinHandler();
    if (isNewControlMode())
    {
        setHandler(m_nextControlMode);                 // manual->full
        m_currentHandler->setSpinMode(m_spinMode);     // ensures that the new control mode doesn't use his last "internal spin mode"
    }
    if (isNewSpinMode())
    {
        m_currentHandler->setSpinMode(m_nextSpinMode); // auto->full; manual->single; 
    }
    m_currentHandler->activateSpinHandler();
    updateModes();
}
bool WolffFiniteStateMachine::isLeavingCurrentState() const
{
    return m_currentHandler->isLeaving();
}
void WolffFiniteStateMachine::blockSwitches(ControlMode& controlmode, SpinMode& spin_mode) const
{
    if(controlmode != m_nextControlMode)
    {
        controlmode = m_nextControlMode;
    }
    if(spin_mode != m_nextSpinMode)
    {
        spin_mode = m_nextSpinMode;
    }
}
void WolffFiniteStateMachine::runAlgorithm(IGuiArray2d& RaySpin, std::mt19937& rng, float temperature)
{
    m_currentHandler->createCluster(RaySpin, rng, temperature);
}
void WolffFiniteStateMachine::handleExtremeTemperature(float& actual_temp, float minTemp)
{
    if(actual_temp < minTemp && m_controlMode == ControlMode::Automatic && m_spinMode == SpinMode::FullSpin)
    {
        actual_temp = minTemp;
    }
}
