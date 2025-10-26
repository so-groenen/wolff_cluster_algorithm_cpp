#ifndef WOLFF_FINITE_STATE_MACHINE_HPP
#define WOLFF_FINITE_STATE_MACHINE_HPP


#include "spin_control_modes.hpp"
#include "spin_handlers/abstract_spin_handler.hpp"
#include "spin_handlers/automatic_spin_handler.hpp"
#include "spin_handlers/manual_spin_handler.hpp"
 
class WolffFiniteStateMachine
{
    // ControlMode m_controlMode{};
    // SpinMode m_spinMode{};

    ControlMode m_nextControlMode{};
    SpinMode m_nextSpinMode{};
    bool m_isMultiSpinChange{};
    
    AbstractSpinHandler* m_currentHandler{};
    ManualSpinHandler m_manualHandler{};       
    AutomaticSpinHandler m_automaticHandler{};
    // void updateModes();
    void setSpinHandler(ControlMode mode);
    // bool isNewSpinMode() const ;
    // bool isNewControlMode() const ;
    bool isCurrentSpinMode(SpinMode spinMode) const;
    bool isCurrentControlMode(ControlMode controlMode) const;
    
public:
    WolffFiniteStateMachine(ControlMode controlMode, SpinMode spinMode);
    void handleEvents(ControlMode controlMode, SpinMode spinMode);
    void transitionState();
    bool isLeavingCurrentState() const;
    void blockSwitches(ControlMode& controlmode, SpinMode& spin_mode) const;
    void runAlgorithm(AbstractWolffArray2d& RaySpin, std::mt19937& rng, float temperature);
    void run(ControlMode controlMode, SpinMode spinMode, AbstractWolffArray2d& RaySpin, std::mt19937& rng, float temperature);
    void handleExtremeTemperature(float& actual_temp, float minTemp);
};

#endif