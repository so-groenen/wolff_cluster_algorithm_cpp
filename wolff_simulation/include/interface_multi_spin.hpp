#ifndef MULTI_SPIN_HPP
#define MULTI_SPIN_HPP

#include <iostream>
class IMultiSpin
{
public:
    virtual void resetCount() = 0;
    virtual void setSpinPerFrame(size_t num) = 0;
    virtual ~IMultiSpin() = default;
};

#endif