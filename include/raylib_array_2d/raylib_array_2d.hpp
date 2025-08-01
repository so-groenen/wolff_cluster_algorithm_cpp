#ifndef RayArray2d_H
#define RayArray2d_H
#include "Spin2D.hpp"
#include "array_point.hpp"
#include "interface_gui_array_2d.hpp"

#include <random>

namespace ray
{
    #include <raylib.h>
}


#define spin_up           1
#define spin_down        -1
extern ray::Color spin_up_color;
extern ray::Color spin_down_color;

extern int SPIN_RECT_HEIGHT;    
extern int SPIN_RECT_WIDTH;     
// extern int X_SPIN_STEP;          // X_SPIN_STEP >= SPIN_RECT_WIDTH
// extern int Y_SPIN_STEP;          // Y_SPIN_STEP >= SPIN_RECT_HEIGHT
#define X_SPIN_STEP        (SPIN_RECT_WIDTH)      // X_SPIN_STEP >= SPIN_RECT_WIDTH
#define Y_SPIN_STEP        (SPIN_RECT_HEIGHT)    // Y_SPIN_STEP >= SPIN_RECT_HEIGHT
extern int X_OFFSET;            
extern int Y_OFFSET;        


namespace raylib_array_2d
{
    using spin_2d::Spin2D;
    using spin_2d::ArrayPoint;
    
    inline void setSpinRectHeight(int x) {SPIN_RECT_HEIGHT = x;}
    inline void setSpinRectWidth(int x){SPIN_RECT_WIDTH = x;}
    // inline void set_spin_x_step(int x){X_SPIN_STEP = x;}
    // inline void set_spin_y_step(int x){Y_SPIN_STEP = x;}
    inline void setXoffset(int x){X_OFFSET = x;}
    inline void setYoffset(int y){Y_OFFSET = y;}
    inline int getXoffset(){return X_OFFSET;}
    inline int getYoffset(){return Y_OFFSET;}
    inline void setSpinUpColor(ray::Color x){spin_up_color = x;}
    inline void setSpinDownColor(ray::Color x){spin_down_color = x;}


    class RayArray2d : public IGuiArray2d
    {
        Spin2D<int64_t> m_Spin_matrix;
        int64_t m_cols{};
        int64_t m_rows{};
        ray::Color getColor(int64_t i, int64_t j) const;
        ArrayPoint getRealPos(int64_t x_index, int64_t y_index) const;
        ArrayPoint getRealPos(const ArrayPoint& other) const;
        bool isMouseInMatrix() const;
    public:
        RayArray2d(int64_t rows, int64_t cols);      
        RayArray2d(Spin2D<int64_t>&& Matrix);        // move constructor
        ~RayArray2d() = default;
        void randomizeSpins(std::mt19937& rng);
        void drawAll(void) const;
        int64_t getWidth(void) const override;
        int64_t getHeight(void) const override;
        int64_t& at(const ArrayPoint& point) override;
        ArrayPoint getHoverPoint() const override;
        void setNeighbourhood(const ArrayPoint& coordinate, std::array<ArrayPoint,4> & neigbourhood) const override;
        bool isClicked() const override;
        void highlightSelectedSpin(void);
        // Spin2D<int64_t>& getMatrix(void);
        const int64_t& at(const ArrayPoint& point) const;
    };
}

#endif