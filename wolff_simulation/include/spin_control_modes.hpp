#ifndef SPIN_CONTROL_MODES_HPP
#define SPIN_CONTROL_MODES_HPP

#include <iostream>

enum class SpinMode
{
    FullSpin  = 0,
    SingleSpin = 1,
    DoubleSpin = 2,
    QuadrupleSpin = 4,
    InfiniteSpin = INT32_MAX,
};
enum class ControlMode
{
    Automatic,
    Manual,
};



#endif