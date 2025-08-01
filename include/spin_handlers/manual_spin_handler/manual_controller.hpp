#ifndef MANUAL_CONTROLLER_HPP
#define MANUAL_CONTROLLER_HPP

#include "interface_gui_array_2d.hpp"

class ManualController
{
    enum class Algorithm
    {
        WAIT,
        RUN
    };
    Algorithm algorithm = Algorithm::WAIT;
public:
    ManualController()  = default;
    ~ManualController() = default; 
    void setAlgorithmToWait();
    void setAlgorithmToRun();
    bool isAlgorithmWaiting() const;
    bool isAlgorithmRunning() const;
    bool setSeedManual(const IGuiArray2d& spinMatrix, ArrayPoint& seedPosition);
};

#endif