#include "spin_handlers/manual_spin_handler/manual_controller.hpp"

 
void ManualController::setAlgorithmToWait()
{
    algorithm = Algorithm::WAIT;
}
void ManualController::setAlgorithmToRun()
{
    algorithm = Algorithm::RUN;
}
bool ManualController::isAlgorithmWaiting() const
{
    return (algorithm == Algorithm::WAIT);
}
bool ManualController::isAlgorithmRunning() const
{
    return (algorithm == Algorithm::RUN);
}
bool ManualController::setSeedManual(const IGuiArray2d& spinMatrix, ArrayPoint& seedPosition)
{
    if(spinMatrix.isClicked())
    {
        seedPosition = spinMatrix.getHoverPoint();
        return true;
    }
    return false;
}
