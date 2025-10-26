#include "wolff_finite_state_machine.hpp"
#define BOOL_TO_STR(X) ( (X)? "True" : "False")

bool WolffFiniteStateMachine::isCurrentControlMode(ControlMode other_controlMode) const
{
    return m_currentHandler->getControlMode() == other_controlMode;
}
bool WolffFiniteStateMachine::isCurrentSpinMode(SpinMode other_spinMode) const
{
    return m_currentHandler->getSpinMode() == other_spinMode;
}

void WolffFiniteStateMachine::setSpinHandler(ControlMode mode)
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

WolffFiniteStateMachine::WolffFiniteStateMachine(ControlMode controlMode, SpinMode spinMode)
    : 
        m_nextControlMode{controlMode},
        m_nextSpinMode{spinMode}
{
    setSpinHandler(controlMode);
    m_currentHandler->setClusterCreator(spinMode);
    m_currentHandler->activateSpinHandler();
}
void WolffFiniteStateMachine::handleEvents(ControlMode input_controlMode, SpinMode input_spinMode)
{


    if (!m_currentHandler->isActif() || (isCurrentSpinMode(input_spinMode) && isCurrentControlMode(input_controlMode)))
        return;

    // if (isCurrentSpinMode(SpinMode::InfiniteSpin))
    // {
    //     m_nextSpinMode = input_spinMode;
    //     m_currentHandler->setToLeaving();
    //     // puts("DEBUG: InfiniteSpin -> FullCluster!");
    //     // return;
    // }
    if (!isCurrentSpinMode(input_spinMode)) // else if 
    {
        // m_nextSpinMode = input_spinMode;

        // if (!isCurrentSpinMode(SpinMode::FullSpin) && input_spinMode == SpinMode::FullSpin)
        // {
        //     m_nextSpinMode      = SpinMode::InfiniteSpin;
        //     m_isMultiSpinChange = true;
        //     puts("DEBUG: MultiSpin -> FullCluster via InfiniteSpin!");
        // }
        if (!isCurrentSpinMode(SpinMode::FullSpin) && input_spinMode != SpinMode::FullSpin) // else if
        {
            m_nextSpinMode      = input_spinMode;
            m_isMultiSpinChange = true;
            puts("DEBUG: MultiSpin -> MultiSpin!");
        }
        else
        {
            m_nextSpinMode = input_spinMode;
            m_currentHandler->setToLeaving();
            puts("DEBUG: FullCluster -> MultiSpin!");
        }
    }
    if (!isCurrentControlMode(input_controlMode))
    {
        m_nextControlMode = input_controlMode;
        m_currentHandler->setToLeaving();
    }
}
void WolffFiniteStateMachine::transitionState()
{
    if (!m_currentHandler->isFinished() && !m_isMultiSpinChange)
        return;
    

    if (m_isMultiSpinChange)
    {      
        m_currentHandler->setClusterCreator(m_nextSpinMode);  
        m_isMultiSpinChange = false;
        return;
    }
    

    m_currentHandler->deactivateSpinHandler();          // deactivating/activating wil reset the spin count for the singleWolffs
    if (!isCurrentControlMode(m_nextControlMode))
    {
        SpinMode currentSpinMode {m_currentHandler->getSpinMode()};
        setSpinHandler(m_nextControlMode);                
        m_currentHandler->setClusterCreator(currentSpinMode);  
        puts("DEBUG: new control mode.");
    }
    else if (!isCurrentSpinMode(m_nextSpinMode))
    {
        m_currentHandler->setClusterCreator(m_nextSpinMode);  
        puts("DEBUG: new speed set.");
    }
    m_currentHandler->activateSpinHandler();

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
void WolffFiniteStateMachine::runAlgorithm(AbstractWolffArray2d& RaySpin, std::mt19937& rng, float temperature)
{
    m_currentHandler->createCluster(RaySpin, rng, temperature);
}
void WolffFiniteStateMachine::handleExtremeTemperature(float& inputTemp, float minTempCutoff)
{
    if(inputTemp < minTempCutoff && isCurrentControlMode(ControlMode::Automatic) && isCurrentSpinMode(SpinMode::FullSpin))
    {
        inputTemp = minTempCutoff;
    }
}
void WolffFiniteStateMachine::run(ControlMode controlMode, SpinMode spinMode, AbstractWolffArray2d& RaySpin, std::mt19937& rng, float temperature)
{
    handleEvents(controlMode, spinMode);
    transitionState();
    m_currentHandler->createCluster(RaySpin, rng, temperature);
}
