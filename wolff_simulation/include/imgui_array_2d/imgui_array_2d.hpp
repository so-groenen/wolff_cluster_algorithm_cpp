#ifndef IMGUI_ARRAY_HPP
#define IMGUI_ARRAY_HPP
#include "PeriodicArray2d.hpp"
#include "array_point.hpp"
#include "interface_gui_array_2d.hpp"

#include <random>

namespace imgui_array_2d
{
    using periodic_array_2d::PeriodicArray2d;
    using periodic_array_2d::ArrayPoint;

    class MyGuiArray : public AbstractWolffArray2d
    {
        PeriodicArray2d<int> m_Spin_matrix;
    public:
        static int spinUp();
        static int spinDown();

        MyGuiArray(int rows, int cols);      
        ~MyGuiArray() = default;
        void randomizeSpins(std::mt19937& rng);
        int getWidth(void) const override;
        int getHeight(void) const override;
        int& at(const ArrayPoint& point) override; //
        int at(int x, int y) const; //
        void setNeighbourhood(const ArrayPoint& coordinate, std::array<ArrayPoint,4> & neigbourhood) const override; // can be removed soehow?

    };
}

#endif