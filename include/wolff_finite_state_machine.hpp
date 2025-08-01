#ifndef WOLFF_FINITE_STATE_MACHINE_HPP
#define WOLFF_FINITE_STATE_MACHINE_HPP


#include "spin_control_modes.hpp"
#include "spin_handlers/abstract_spin_handler.hpp"
#include "spin_handlers/automatic_spin_handler.hpp"
#include "spin_handlers/manual_spin_handler.hpp"
 
class WolffFiniteStateMachine
{
    ControlMode m_controlMode{};
    SpinMode m_spinMode{};

    ControlMode m_nextControlMode{};
    SpinMode m_nextSpinMode{};

    
    AbstractSpinHandler* m_currentHandler{};
    ManualSpinHandler m_manualHandler{};       
    AutomaticSpinHandler m_automaticHandler{};
    void updateModes();
    void setHandler(ControlMode mode);
    bool isNewSpinMode() const ;
    bool isNewControlMode() const ;
public:
    WolffFiniteStateMachine(ControlMode controlMode, SpinMode spinMode);
    void handleEvents(ControlMode controlMode, SpinMode spinMode);
    void transitionState();
    bool isLeavingCurrentState() const;
    void blockSwitches(ControlMode& controlmode, SpinMode& spin_mode) const;
    void runAlgorithm(IGuiArray2d& RaySpin, std::mt19937& rng, float temperature);
    void handleExtremeTemperature(float& actual_temp, float minTemp);
};

#endif