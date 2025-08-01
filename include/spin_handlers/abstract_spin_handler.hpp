#ifndef ABSTRACT_SPIN_HANDLER_HPP
#define ABSTRACT_SPIN_HANDLER_HPP

#include "interface_cluster_creator.hpp"
#include "spin_control_modes.hpp"

class AbstractSpinHandler : public IClusterCreator
{
    enum class State
    {
        INACTIF,
        ACTIF,
        LEAVING,
        FINISHED,
    };
    State m_state {State::ACTIF};
public:
    AbstractSpinHandler()  = default;
    virtual ~AbstractSpinHandler()
    {
    }
    virtual void setSpinMode(SpinMode mode) = 0;
    virtual void activateSpinHandler() = 0;
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