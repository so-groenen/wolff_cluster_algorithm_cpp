#include "imgui_array_2d/imgui_array_2d.hpp"

namespace imgui_array_2d
{
    int MyGuiArray::spinUp()
    {
        return +1;
    }
    int MyGuiArray::spinDown()
    {
        return -1;
    }

    MyGuiArray::MyGuiArray(int rows, int cols)
        : m_Spin_matrix{rows, cols}
    {
    }          
    void MyGuiArray::randomizeSpins(std::mt19937& rng)
    {
        std::uniform_int_distribution<int> rand_int{0,1};
        int rand = 0;
        for (int i = 0; i < getHeight(); i++)
        {
            for (int j = 0; j < getHeight(); j++)
            {
                // rand = (int)(rng());
                // rand = distrib(rng);/
                m_Spin_matrix(i, j) = 1 - 2*rand_int(rng);// (rand%2);
            }
        }
    }
    int MyGuiArray::getWidth(void) const
    {
        return (int)m_Spin_matrix.get_cols();
    }
    int MyGuiArray::getHeight(void) const
    {
        return (int)m_Spin_matrix.get_rows();
    }
    int& MyGuiArray::at(const ArrayPoint& point)
    {
        return m_Spin_matrix(point);
    }
    int MyGuiArray::at(int x, int y) const
    {
        return m_Spin_matrix(y, x);
    }
    void MyGuiArray::setNeighbourhood(const ArrayPoint& coordinate, std::array<ArrayPoint,4> & neigbourhood) const
    {
        return m_Spin_matrix.set_neighbourhood(coordinate, neigbourhood);
    }
}