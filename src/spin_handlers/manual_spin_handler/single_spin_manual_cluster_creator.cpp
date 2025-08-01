#include "spin_handlers/manual_spin_handler/single_spin_manual_cluster_creator.hpp"

void SingleSpinManualClusterCreator::checkWaitingStatus()   
{
    if(m_controller.isAlgorithmWaiting() && m_spinHandler->isLeaving())
    {
        m_spinHandler->setToFinished();
    }
}
bool SingleSpinManualClusterCreator::initClusterManually(IGuiArray2d& spinMatrix)
{
    ArrayPoint seedPosition{};
    if((m_controller.setSeedManual(spinMatrix, seedPosition)) && m_controller.isAlgorithmWaiting())
    {
        m_wolff.initQueue(spinMatrix, seedPosition);
        return true;
    }
    return false;
}  


// SingleSpinManualClusterCreator(WolffState* state)
SingleSpinManualClusterCreator::SingleSpinManualClusterCreator(AbstractSpinHandler* state)
    : m_spinHandler{state}
{
}
void SingleSpinManualClusterCreator::activateManualClusterCreator()
{
    m_controller.setAlgorithmToWait();
    m_spinHandler->setToActif();
}  
void SingleSpinManualClusterCreator::createCluster(IGuiArray2d& spinMatrix, std::mt19937& rng, float temperature)
{
    checkWaitingStatus();
    if(initClusterManually(spinMatrix))
    {
        m_controller.setAlgorithmToRun();
    }

    while(m_controller.isAlgorithmRunning())
    {
        if(m_wolff.isEmptyQueue() && m_spinHandler->isActif())
        {
            m_controller.setAlgorithmToWait();
            break;
        }
        else if(m_wolff.isEmptyQueue() &&  m_spinHandler->isLeaving())
        {
            m_spinHandler->setToFinished();
            break;
        }

        if(m_wolff.isNewNeighbourhood() || m_wolff.isNeighbourhoodVisited())
        {
            m_wolff.createNewNeighbourhood(spinMatrix);
            m_wolff.resetSpinCounter();
        }              
        if (m_wolff.attemptSingleSpinUpdate(spinMatrix, rng, temperature))
        {
            m_wolff.updateSpinCounter();
            break;
        }   
    };
}
