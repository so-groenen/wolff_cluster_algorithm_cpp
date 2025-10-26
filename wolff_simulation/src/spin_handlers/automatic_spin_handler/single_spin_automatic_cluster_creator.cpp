#include "spin_handlers/automatic_spin_handler/single_spin_automatic_cluster_creator.hpp"


void SingleSpinAutomaticClusterCreator::initCluster(AbstractWolffArray2d& spinMatrix, std::mt19937& rng)
{
    ArrayPoint seedPosition = m_controller.getSeedRandom(spinMatrix, rng);

    spinMatrix.seed.SelectSeed(seedPosition.x, seedPosition.y);
    m_wolff.initQueue(spinMatrix);

}

SingleSpinAutomaticClusterCreator::SingleSpinAutomaticClusterCreator(AbstractSpinHandler* parent_state)
    :  m_spinHandler{parent_state}
{
}
void SingleSpinAutomaticClusterCreator::setSpinPerFrame(size_t N)
{
    m_spinsPerFrame = N;
} 
void SingleSpinAutomaticClusterCreator::resetCount() 
{
    m_spinCounter = 0;
}

void SingleSpinAutomaticClusterCreator::createCluster(AbstractWolffArray2d& spinMatrix, std::mt19937& rng, float temperature)
{
    while(!m_spinHandler->isInactif())                                          //add "clusterspincounter"
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
        
        if(m_wolff.attemptSingleSpinUpdate(spinMatrix, rng, temperature))
        {
            m_spinCounter++;
            if (m_spinCounter == m_spinsPerFrame)
            {
                resetCount();
                break;
            }
        }
        
        // if(m_wolff.isNewNeighbourhood() || m_wolff.isNeighbourhoodVisited())
        // {
        //     m_wolff.createNewNeighbourhood(spinMatrix);
        //     m_wolff.resetSpinCounter();
        // }               
        // if(m_wolff.attempt_Single_Spin_UpdatespinMatrix, rng, temperature))
        // {
        //     m_wolff.updateSpinCounter();                                        //add "clusterspincounter"
        //     break;
        // }
    };
}
 