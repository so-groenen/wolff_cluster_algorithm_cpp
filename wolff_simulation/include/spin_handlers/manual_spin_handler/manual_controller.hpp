#ifndef MANUAL_CONTROLLER_HPP
#define MANUAL_CONTROLLER_HPP

#include "interface_gui_array_2d.hpp"
#include "wolff_algorithms/base_wolff_algorithm.hpp"

class ManualController
{
    enum class Algorithm
    {
        WAIT,
        RUN
    };
    Algorithm m_algorithm {Algorithm::WAIT};
    // void setControllerState(Algorithm state);
public:
    ManualController()  = default;
    ~ManualController() = default; 
    bool initClusterManually_CONTROLLER(BaseWolffAlgorithm& wolff, AbstractWolffArray2d& spinMatrix);
    void awaitInput();
    void run();
    bool isAwaitingInput() const;
    bool isRunning() const;
    // bool setSeedManual(const AbstractWolffArray2d& spinMatrix, ArrayPoint& seedPosition);
};

#endif