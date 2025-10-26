#ifndef ABSTRACT_SPIN_HANDLER_HPP
#define ABSTRACT_SPIN_HANDLER_HPP

#include "interface_cluster_creator.hpp"
#include "spin_control_modes.hpp"

class AbstractSpinHandler : public IClusterCreator
{
protected:
    enum class State
    {
        INACTIF,
        ACTIF,
        LEAVING,
        FINISHED,
    };
    void setState(State state);
private:
    State m_state {State::ACTIF};
    SpinMode m_spinMode;                
public:
    AbstractSpinHandler()  = default;
    virtual ~AbstractSpinHandler() = default;
    virtual void setClusterCreator(SpinMode mode) = 0; //handle spinMode?
    virtual void activateSpinHandler() = 0;
    virtual ControlMode getControlMode() const = 0;
    static size_t spinModeToNum(SpinMode spinMode);
    SpinMode getSpinMode() const;
    void setSpinMode(SpinMode mode);
    void deactivateSpinHandler();
    void setToLeaving();
    void setToFinished();
    void setToActif();
    bool isLeaving() const;
    bool isFinished() const;
    bool isActif() const;
    bool isInactif() const;
};


#endif