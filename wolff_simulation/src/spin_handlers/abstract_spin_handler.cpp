#include "spin_handlers/abstract_spin_handler.hpp"


void AbstractSpinHandler::setState(State state)
{
    m_state = state;
}

SpinMode AbstractSpinHandler::getSpinMode() const
{
    return m_spinMode;
}
size_t AbstractSpinHandler::spinModeToNum(SpinMode spinMode) 
{
    return static_cast<size_t>(spinMode);
}

void AbstractSpinHandler::setSpinMode(SpinMode mode) 
{
    m_spinMode = mode;    
}
void AbstractSpinHandler::deactivateSpinHandler()
{
    m_state = State::INACTIF;
}
void AbstractSpinHandler::setToLeaving()
{
    m_state = State::LEAVING;
}
void AbstractSpinHandler::setToFinished()
{
    m_state = State::FINISHED;
}
void AbstractSpinHandler::setToActif()
{
    m_state = State::ACTIF;
}
bool AbstractSpinHandler::isLeaving() const
{
    return (m_state == State::LEAVING);
}
bool AbstractSpinHandler::isFinished() const
{
    return (m_state == State::FINISHED);
}
bool AbstractSpinHandler::isActif() const
{
    return (m_state == State::ACTIF);
}
bool AbstractSpinHandler::isInactif() const
{
    return (m_state == State::INACTIF);
}

