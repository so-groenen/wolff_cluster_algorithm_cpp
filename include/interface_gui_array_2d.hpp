#ifndef IGUIARRAY2D_HPP
#define IGUIARRAY2D_HPP
#include <array>
#include "array_point.hpp"
#include <iostream>

using spin_2d::ArrayPoint;

class IGuiArray2d
{
public:
    virtual int64_t getWidth(void) const = 0;
    virtual int64_t getHeight(void) const = 0;
    virtual ArrayPoint getHoverPoint() const = 0;
    virtual bool isClicked() const = 0;
    virtual void setNeighbourhood(const ArrayPoint& p, std::array<ArrayPoint,4> & neigbourhood) const = 0;
    virtual int64_t& at(const spin_2d::ArrayPoint& p) = 0;
    ~IGuiArray2d() = default;
};
#endif