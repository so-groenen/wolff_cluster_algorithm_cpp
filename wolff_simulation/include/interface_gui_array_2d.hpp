#ifndef IGUIARRAY2D_HPP
#define IGUIARRAY2D_HPP
#include <array>
#include "array_point.hpp"
#include <iostream>

using periodic_array_2d::ArrayPoint; 

class WolffSeed
{
    ArrayPoint m_seed{};
    bool m_isSeedSelected{};
public:
    ArrayPoint getSeed() const 
    {
        return m_seed;
    }
    bool isSeedSelected() const 
    {
        return m_isSeedSelected;
    }
    void SelectSeed(int x, int y)
    {
        m_seed.x = x;
        m_seed.y = y;
        m_isSeedSelected = true;
    }
    void resetSeed()
    {
        m_isSeedSelected = false;
    }
};

struct ArrayInterFace
{
    virtual int getWidth(void) const = 0;
    virtual int getHeight(void) const = 0;
    virtual void setNeighbourhood(const ArrayPoint& p, std::array<ArrayPoint,4> & neigbourhood) const = 0;
    virtual int& at(const periodic_array_2d::ArrayPoint& p) = 0;
    ~ArrayInterFace() = default;
};

class IGuiArray2d
{
public:

    virtual int getWidth(void) const = 0;
    virtual int getHeight(void) const = 0;
    virtual bool isSeedSelected() const = 0;
    virtual void resetSeed()= 0;
    virtual ArrayPoint getSeed() const = 0;
    virtual void SelectSeed(int x, int y) = 0;

    // internal functions used by the finite state machines:
    virtual void setNeighbourhood(const ArrayPoint& p, std::array<ArrayPoint,4> & neigbourhood) const = 0;
    virtual int& at(const periodic_array_2d::ArrayPoint& p) = 0;
    ~IGuiArray2d() = default;

};

class AbstractWolffArray2d : public ArrayInterFace
{
public:
    WolffSeed seed;
    ~AbstractWolffArray2d() = default; 
}; 


#endif