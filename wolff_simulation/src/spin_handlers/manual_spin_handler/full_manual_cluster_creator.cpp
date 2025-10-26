#include "spin_handlers/manual_spin_handler/full_manual_cluster_creator.hpp"

bool FullManualClusterCreator::initClusterManually(AbstractWolffArray2d& spinMatrix)  //use controller instead
{
    if(spinMatrix.seed.isSeedSelected())
    {
        m_wolff.initQueue(spinMatrix);
        return true;
    }
    return false;
}
FullManualClusterCreator::FullManualClusterCreator(AbstractSpinHandler* state)
    : m_handler_state{state}
{  
}
void FullManualClusterCreator::activateManualController()
{
    m_controller.awaitInput();
    // m_handler_state->setToActif();
}  
void FullManualClusterCreator::createCluster(AbstractWolffArray2d& spinMatrix, std::mt19937& rng, float temperature)
{
    if (m_controller.isAwaitingInput() && m_handler_state->isLeaving())
    {
        m_handler_state->setToFinished();
    }
    else if(m_controller.isAwaitingInput() && m_controller.initClusterManually_CONTROLLER(m_wolff, spinMatrix))
    {
        m_controller.run();
    }
    // else if(m_controller.isAwaitingInput() && initClusterManually(spinMatrix))
    // {
    //     m_controller.run();
    // }
    if(m_controller.isRunning()) // "else if" ==> "if"
    {
        m_wolff.performWolffAlgorithm(spinMatrix, rng, temperature);
        m_controller.awaitInput();
    }
}