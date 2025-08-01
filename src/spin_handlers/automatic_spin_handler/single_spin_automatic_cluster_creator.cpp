#include "spin_handlers/automatic_spin_handler/single_spin_automatic_cluster_creator.hpp"


void SingleSpinAutomaticClusterCreator::initCluster(IGuiArray2d& spinMatrix, std::mt19937& rng)
{
    ArrayPoint seedPosition = m_controller.getSeedRandom(spinMatrix, rng);
    m_wolff.initQueue(spinMatrix, seedPosition);
}

SingleSpinAutomaticClusterCreator::SingleSpinAutomaticClusterCreator(AbstractSpinHandler* parent_state)
    :  m_spinHandler{parent_state}
{
}
void SingleSpinAutomaticClusterCreator::createCluster(IGuiArray2d& spinMatrix, std::mt19937& rng, float temperature)
{
    while(!m_spinHandler->isInactif())  
    {
        if(m_wolff.isEmptyQueue() && m_spinHandler->isLeaving()) 
        {   
            m_spinHandler->setToFinished();
            break;
        } 
        else if(m_wolff.isEmptyQueue())
        {
            initCluster(spinMatrix, rng);
        }
        if(m_wolff.isNewNeighbourhood() || m_wolff.isNeighbourhoodVisited())
        {
            m_wolff.createNewNeighbourhood(spinMatrix);
            m_wolff.resetSpinCounter();
        }               
        if(m_wolff.attemptSingleSpinUpdate(spinMatrix, rng, temperature))
        {
            m_wolff.updateSpinCounter();
            break;
        }
    };
}
 