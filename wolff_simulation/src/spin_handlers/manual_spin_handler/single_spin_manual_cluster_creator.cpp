#include "spin_handlers/manual_spin_handler/single_spin_manual_cluster_creator.hpp"

void SingleSpinManualClusterCreator::checkWaitingStatus()   
{
    if(m_controller.isAwaitingInput() && m_spinHandler->isLeaving())
    {
        m_spinHandler->setToFinished();
    }
}
bool SingleSpinManualClusterCreator::initClusterManually(AbstractWolffArray2d& spinMatrix) //use controller instead
{
    if(spinMatrix.seed.isSeedSelected() && m_controller.isAwaitingInput())
    {
        m_wolff.initQueue(spinMatrix); 
        return true;
    }
    return false;
}  


// SingleSpinManualClusterCreator(WolffState* state)
SingleSpinManualClusterCreator::SingleSpinManualClusterCreator(AbstractSpinHandler* state)
    : m_spinHandler{state}
{
}
void SingleSpinManualClusterCreator::setSpinPerFrame(size_t N)
{
    m_spinsPerFrame = N;
} 
void SingleSpinManualClusterCreator::resetCount() 
{
    m_spinCounter = 0;
}

void SingleSpinManualClusterCreator::activateManualController()
{
    m_controller.awaitInput();
    // m_spinHandler->setToActif();
}  
void SingleSpinManualClusterCreator::createCluster(AbstractWolffArray2d& spinMatrix, std::mt19937& rng, float temperature)
{
    // checkWaitingStatus();
    if(m_controller.isAwaitingInput() && m_spinHandler->isLeaving())
    {
        m_spinHandler->setToFinished();
    }
    else if (m_controller.isAwaitingInput() && m_controller.initClusterManually_CONTROLLER(m_wolff, spinMatrix))
    {
        m_controller.run();
    }
    
    // if(initClusterManually(spinMatrix))
    // {
    //     m_controller.run();
    // }
    
    while(m_controller.isRunning())                                // <<<<<<< add a spin counter to count number of spins added in the cluster
    {
        if(m_wolff.isEmptyQueue() && m_spinHandler->isActif())
        {
            m_controller.awaitInput();
            break;
        }
        else if(m_wolff.isEmptyQueue() &&  m_spinHandler->isLeaving())
        {
            m_spinHandler->setToFinished();
            break;
        }

        if(m_wolff.attemptSingleSpinUpdate(spinMatrix, rng, temperature))
        {
            m_spinCounter++;
            if (m_spinCounter == m_spinsPerFrame)
            {
                resetCount();
                break;
            }
        }
    };
}
