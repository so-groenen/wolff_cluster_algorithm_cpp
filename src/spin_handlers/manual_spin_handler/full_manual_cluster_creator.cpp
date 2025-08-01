#include "spin_handlers/manual_spin_handler/full_manual_cluster_creator.hpp"

bool FullManualClusterCreator::initClusterManually(IGuiArray2d& spinMatrix)
{
    ArrayPoint seedPosition{};
    if(m_controller.setSeedManual(spinMatrix, seedPosition))
    {
        m_wolff.initQueue(spinMatrix, seedPosition);
        return true;
        // m_controller.setAlgorithmToRun();
    }
    return false;
}
FullManualClusterCreator::FullManualClusterCreator(AbstractSpinHandler* state)
    : m_handler_state{state}
{  
}
void FullManualClusterCreator::activateManualClusterCreator()
{
    m_controller.setAlgorithmToWait();
    m_handler_state->setToActif();
}  
void FullManualClusterCreator::createCluster(IGuiArray2d& spinMatrix, std::mt19937& rng, float temperature)
{
    if (m_controller.isAlgorithmWaiting() && m_handler_state->isLeaving())
    {
        m_handler_state->setToFinished();
    }
    else if(m_controller.isAlgorithmWaiting())
    {
        if(initClusterManually(spinMatrix))
            m_controller.setAlgorithmToRun();
    }
    else if(m_controller.isAlgorithmRunning())
    {
        m_wolff.performWolffAlgorithm(spinMatrix, rng, temperature);
        m_controller.setAlgorithmToWait();
    }
}