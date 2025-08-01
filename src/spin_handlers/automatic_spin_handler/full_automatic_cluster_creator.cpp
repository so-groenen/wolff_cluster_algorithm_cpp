#include "spin_handlers/automatic_spin_handler/full_automatic_cluster_creator.hpp"


void FullAutomaticClusterCreator::setRandomPosition(const ArrayPoint& seedPosition)
{
    m_wolff.setSeedPosition(seedPosition);
}
void FullAutomaticClusterCreator::initCluster(IGuiArray2d& spinMatrix, std::mt19937& rng) 
{
    ArrayPoint seedPosition = m_controller.getSeedRandom(spinMatrix, rng);
    m_wolff.initQueue(spinMatrix, seedPosition);
}
FullAutomaticClusterCreator::FullAutomaticClusterCreator(AbstractSpinHandler* parent_state)
    :  m_spinHandler{parent_state}
{
}
void FullAutomaticClusterCreator::createCluster(IGuiArray2d& spinMatrix, std::mt19937& rng, float temperature)
{
    if (m_spinHandler->isLeaving())
    {
        m_spinHandler->setToFinished();
    }
    else
    {
        initCluster(spinMatrix, rng);
        m_wolff.performWolffAlgorithm(spinMatrix, rng, temperature);
    }
}
 