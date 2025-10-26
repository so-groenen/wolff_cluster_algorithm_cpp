#include "spin_handlers/manual_spin_handler/manual_controller.hpp"
#include "wolff_algorithms/base_wolff_algorithm.hpp"
// void ManualController::setControllerState(Algorithm state)
// {
//     m_algorithm = state; //rename stuff
// }

bool ManualController::initClusterManually_CONTROLLER(BaseWolffAlgorithm& wolff, AbstractWolffArray2d& spinMatrix)
{
    if(spinMatrix.seed.isSeedSelected())
    {
        wolff.initQueue(spinMatrix);
        return true;
    }
    return false;
}
void ManualController::awaitInput()
{
    m_algorithm = Algorithm::WAIT;
}
void ManualController::run()
{
    m_algorithm = Algorithm::RUN;
}
bool ManualController::isAwaitingInput() const
{
    return (m_algorithm == Algorithm::WAIT);
}
bool ManualController::isRunning() const
{
    return (m_algorithm == Algorithm::RUN);
}
// bool ManualController::setSeedManual(const AbstractWolffArray2d& spinMatrix, ArrayPoint& seedPosition) //This function should not exit
// {
//     // if(spinMatrix.isClicked())
//     // {
//     //     seedPosition = spinMatrix.getHoverPoint();
//     //     return true;
//     // }
//     // return false;
//     if(spinMatrix.seed.isSeedSelected()) // 
//     {
//         seedPosition = spinMatrix.seed.getSeed();
//         return true;
//     }
//     return false;
// }
