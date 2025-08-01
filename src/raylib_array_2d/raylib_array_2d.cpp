#include "raylib_array_2d/raylib_array_2d.hpp"

int SPIN_RECT_HEIGHT = 10;               
int SPIN_RECT_WIDTH  = 10; 
// #define X_SPIN_STEP        (SPIN_RECT_WIDTH)      // X_SPIN_STEP >= SPIN_RECT_WIDTH
// #define Y_SPIN_STEP        (SPIN_RECT_HEIGHT)    // Y_SPIN_STEP >= SPIN_RECT_HEIGHT
int X_OFFSET         = 50;
int Y_OFFSET         = 20;


 
ray::Color spin_up_color   = ray::RED;
ray::Color spin_down_color = ray::BLUE;
namespace raylib_array_2d
{
    RayArray2d::RayArray2d(int64_t rows, int64_t cols)           // uses an in place matrix constructor
        : m_Spin_matrix{rows, cols}
    {
        m_rows   = m_Spin_matrix.get_rows();
        m_cols    = m_Spin_matrix.get_cols();
        std::cout << "Ray: cols " << m_cols << " rows " << m_rows << "\n";
    }
    RayArray2d::RayArray2d(Spin2D<int64_t>&& Matrix)                  // move constructor
        : m_Spin_matrix(std::move(Matrix))                               // call the move constructor 
    {
        m_rows   = Matrix.get_rows();
        m_cols    = Matrix.get_cols();
    }
    ray::Color RayArray2d::getColor(int64_t i, int64_t j) const
    {
        ray::Color spin_color;
        switch (m_Spin_matrix(i, j)) 
        {
        case spin_down:
            spin_color = spin_down_color;
            break;
        case spin_up:
            spin_color = spin_up_color;
            break;   
        default:
            spin_color = ray::BLACK;
            break;
        }
        return spin_color;
    }
    void RayArray2d::randomizeSpins(std::mt19937& rng)
    {
        int64_t rand = 0;
        for (int64_t i = 0; i < m_rows; i++)
        {
            for (int64_t j = 0; j < m_cols; j++)
            {
                rand = (int64_t)(rng());
                m_Spin_matrix(i, j) = 1 - 2* (rand%2);
            }
        }
    }
    void RayArray2d::drawAll(void) const
    {
        for (int64_t i = 0; i < m_rows; i++)
        {
            for (int64_t j = 0; j < m_cols; j++)
            {
                ray::DrawRectangle(j*X_SPIN_STEP + X_OFFSET,
                            i*Y_SPIN_STEP + Y_OFFSET,
                            SPIN_RECT_WIDTH, 
                            SPIN_RECT_HEIGHT, 
                            getColor(i, j));
            }
        }
    }


    // double RayArray2d::drawAllAndGetMag(void) const
    // {
    //     double mag = 0;
    //     for (int64_t y = 0; y < m_height; y++)
    //     {
    //         for (int64_t x = 0; x < m_width; x++)
    //         {
    //             sum += m_Spin_matrix(x, y);
    //             DrawRectangle(x*X_SPIN_STEP + X_OFFSET,
    //                           y*Y_SPIN_STEP + Y_OFFSET,
    //                           SPIN_RECT_WIDTH, 
    //                           SPIN_RECT_HEIGHT, 
    //                           getColor(x, y));
    //         }
    //     }
    //     mag /= (float)(m_height*m_width);
    //     return mag;
    // }



    int64_t RayArray2d::getWidth(void) const
    {
        return m_cols;
    }
    int64_t RayArray2d::getHeight(void) const
    {
        return m_rows;
    }

    bool RayArray2d::isMouseInMatrix() const
        {
            bool is_in_width  = ( (ray::GetMouseX()  >= X_OFFSET) && (ray::GetMouseX() < X_OFFSET + (m_cols*X_SPIN_STEP)) );
            bool is_in_height = ( (ray::GetMouseY()  >= Y_OFFSET) && (ray::GetMouseY() < Y_OFFSET + (m_rows*Y_SPIN_STEP)) );
            return (is_in_width && is_in_height);
        }
    ArrayPoint RayArray2d::getHoverPoint() const
    {   
        return { (ray::GetMouseX()-X_OFFSET)/X_SPIN_STEP, (ray::GetMouseY()-Y_OFFSET)/Y_SPIN_STEP };
    }
    bool RayArray2d::isClicked() const
    {
        return (isMouseInMatrix() &&ray::IsMouseButtonPressed(ray::MOUSE_BUTTON_LEFT));   
    }
    ArrayPoint RayArray2d::getRealPos(int64_t x_index, int64_t y_index) const
    {
        return ArrayPoint(x_index*X_SPIN_STEP + X_OFFSET, y_index*Y_SPIN_STEP + Y_OFFSET);
    }
    ArrayPoint RayArray2d::getRealPos(const ArrayPoint& other) const
    {
        return getRealPos(other.x, other.y);
    }
    void RayArray2d::highlightSelectedSpin(void)
    {
        if(isMouseInMatrix())
        {
            ray::DrawRectangleLines(getRealPos(getHoverPoint()).x,
                                getRealPos(getHoverPoint()).y,
                                X_SPIN_STEP, 
                                Y_SPIN_STEP, 
                                ray::WHITE);
        }
    }


    // Spin2D<int64_t>& RayArray2d::getMatrix(void)
    // {
    //     return m_Spin_matrix;
    // }

    int64_t& RayArray2d::at(const ArrayPoint& point)
    {
        return m_Spin_matrix(point);
    }
    const int64_t& RayArray2d::at(const ArrayPoint& point) const
    {
        return m_Spin_matrix(point);
    }

    void RayArray2d::setNeighbourhood(const ArrayPoint& coordinate, std::array<ArrayPoint,4> & neigbourhood) const
    {
        return m_Spin_matrix.set_neighbourhood(coordinate, neigbourhood);
    }
}