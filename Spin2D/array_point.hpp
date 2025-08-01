#ifndef ARRAY_POINT_HPP
#define ARRAY_POINT_HPP
#include <iostream>

namespace spin_2d
{
    struct ArrayPoint
    {
        int64_t x{};
        int64_t y{};
        ArrayPoint() = default;
        ArrayPoint(int64_t X, int64_t Y)
            : x{X}, y{Y}
        {}   
        ~ArrayPoint() = default;
        bool operator==(const ArrayPoint& other) const = default;
    };
}


#endif